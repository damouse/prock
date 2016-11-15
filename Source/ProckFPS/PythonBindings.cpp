// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "PythonBindings.h"

PyDoc_STRVAR(unreal_engine_py_doc, "Unreal Engine Python module.");

// Initialize the python environment and import the native peter components
// The old module code created an import specifically made for output. This has not been carried over.
PythonBindings::PythonBindings() {
	Py_Initialize();
	char *argv[] = { (char *)"UnrealEngine", NULL };
	PySys_SetArgv(1, argv);
	PyEval_InitThreads();

	// Inject new paths into sys.path so we can find our modules
	PyObject *py_sys = PyImport_ImportModule("sys");
	PyObject *py_sys_dict = PyModule_GetDict(py_sys);
	PyObject *py_path = PyDict_GetItemString(py_sys_dict, "path");

	char *native_path = TCHAR_TO_UTF8(*FPaths::Combine(*FPaths::GameSourceDir(), UTF8_TO_TCHAR("")));
	PyObject *py_native_path = PyUnicode_FromString(native_path);
	PyList_Insert(py_path, 0, py_native_path);

	// Add the scripts directory (which contains dependencies)
	char *scripts_path = TCHAR_TO_UTF8(*FPaths::Combine(*FPaths::GameContentDir(), UTF8_TO_TCHAR("Scripts")));
	PyObject *py_scripts_path = PyUnicode_FromString(scripts_path);
	PyList_Insert(py_path, 0, py_scripts_path);

	//UE_LOG(LogProck, Log, TEXT("Python VM initialized: %s. Search path: %s"), UTF8_TO_TCHAR(Py_GetVersion()), UTF8_TO_TCHAR(scripts_path));

	// We don't meed native python handlers. Importing like this is temporary
	this->pypeter = PyImport_ImportModule("pypeter.main");
	if (!this->pypeter) {
		log_py_error();
		return;
	}
	
	// Smoke test call
	PyObject *hello = PyObject_CallMethod(this->pypeter, (char *)"handshake", nullptr);
	if (!hello) {
		log_py_error();
		return;
	}

	printpy(hello);
}

PythonBindings::~PythonBindings() {
	UE_LOG(LogProck, Log, TEXT("Unloading python"));
	PythonGILAcquire();
	Py_Finalize();
}

// Kick off the source code processing job
PyObject* PythonBindings::ImportCode() {
	// Note the hardcoded load path to samplecode.py
	char *sample_path = TCHAR_TO_ANSI(*FPaths::Combine(*FPaths::GameDir(), UTF8_TO_TCHAR("samplecode.py")));
	PyObject *py_native_path = PyUnicode_FromString(sample_path);

	PyObject *ast = PyObject_CallMethod(this->pypeter, (char *)"load_source", (char *)"O", py_native_path);
	if (!ast) {
		log_py_error();
		return nullptr;
	}

	return ast;
}

/*
GIL Management
*/
void PythonBindings::PythonGILRelease() {
#if UEPY_THREADING
	ue_python_gil = PyEval_SaveThread();
#endif
}

void PythonBindings::PythonGILAcquire() {
#if UEPY_THREADING
	PyEval_RestoreThread((PyThreadState *)ue_python_gil);
#endif
}


// Check for a python runtime error and print it if it exists
void log_py_error() {
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

// Note that this isn't going to work for python 3. See the original bindings for the right method
void printpy(PyObject* obj) {
	if (obj) {
		UE_LOG(LogProck, Log, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(obj))));
	} else {
		UE_LOG(LogProck, Error, TEXT("Asked to print null pyobject"));
	}
}

char *pyGetAttr(PyObject* obj, char *attrName) {
	PyObject *item = PyObject_GetAttrString(obj, attrName);
	if (!item) {
		log_py_error();
		return nullptr;
	}

	return PyString_AsString(PyObject_Str(item));
}