// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "PythonBindings.h"

PythonBindings::PythonBindings() {
	//Using the unrealenginepythonmodule only as a means of bootstrapping the python environment
	// Once loaded we just cast the main dict and operate on it (mostly) directly
	python = new FUnrealEnginePythonModule();
	python->StartupModule();

	//python->RunString("import peter");
	//this->RunString("import peter");

	PyObject *import = this->RunString("import peter");
	Py_DECREF(import);

	// So run string uses PyRunString internally, which is for statements and returns nothing. Need a different api.
	PyObject *result = this->RunString("peter.hello()");
	unreal_engine_py_log_error();

	if (!result) {
		unreal_engine_py_log_error();
	} else {
		// It seems the call is executing but not returning anything. Might need a different call method into c python
		this->printpy(result);
		UE_LOG(LogProck, Log, TEXT("Value returned from python: %s"), UTF8_TO_TCHAR(PyString_AsString(result)));
		Py_DECREF(result);
	}
	// This doesn't return a value well, or at all...
}

PythonBindings::~PythonBindings() {
	python->ShutdownModule();
}

PyObject* PythonBindings::RunString(char *str) {
	FScopePythonGIL gil;
	PyObject *eval_ret = PyRun_StringFlags(str, Py_file_input, (PyObject *)python->main_dict, (PyObject *)python->local_dict, nullptr);

	if (!eval_ret) {
		unreal_engine_py_log_error();
		return nullptr;
	}

	//Py_DECREF(eval_ret);
	return eval_ret;
}

// Note that this isn't going to work for python 3. See the original bindings for the right method
void PythonBindings::printpy(PyObject* obj) {
	UE_LOG(LogProck, Log, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(obj))));
}

void PythonBindings::unreal_engine_py_log_error() {
	PyObject *type = NULL;
	PyObject *value = NULL;
	PyObject *traceback = NULL;

	PyErr_Fetch(&type, &value, &traceback);
	PyErr_NormalizeException(&type, &value, &traceback);

	if (!value) {
		PyErr_Clear();
		return;
	}

	char *msg = NULL;
#if PY_MAJOR_VERSION >= 3
	PyObject *zero = PyUnicode_AsUTF8String(PyObject_Str(value));
	if (zero) {
		msg = PyBytes_AsString(zero);
	}
#else
	msg = PyString_AsString(PyObject_Str(value));
#endif
	if (!msg) {
		PyErr_Clear();
		return;
	}

	UE_LOG(LogProck, Error, TEXT("%s"), UTF8_TO_TCHAR(msg));

	// taken from uWSGI ;)
	if (!traceback) {
		PyErr_Clear();
		return;
	}

	PyObject *traceback_module = PyImport_ImportModule("traceback");
	if (!traceback_module) {
		PyErr_Clear();
		return;
	}

	PyObject *traceback_dict = PyModule_GetDict(traceback_module);
	PyObject *format_exception = PyDict_GetItemString(traceback_dict, "format_exception");

	if (format_exception) {
		PyObject *ret = PyObject_CallFunctionObjArgs(format_exception, type, value, traceback, NULL);
		if (!ret) {
			PyErr_Clear();
			return;
		}
		if (PyList_Check(ret)) {
			for (int i = 0; i < PyList_Size(ret); i++) {
				PyObject *item = PyList_GetItem(ret, i);
				if (item) {
					UE_LOG(LogProck, Error, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
				}
			}
		} else {
			UE_LOG(LogProck, Error, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(ret))));
		}
	}

	PyErr_Clear();
}