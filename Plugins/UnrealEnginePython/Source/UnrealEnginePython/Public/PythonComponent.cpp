#include "UnrealEnginePythonPrivatePCH.h"
#include "PythonComponent.h"



UPythonComponent::UPythonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	PythonTickForceDisabled = false;
	PythonDisableAutoBinding = false;


}


// Called when the game starts
void UPythonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (PythonModule.IsEmpty())
		return;

	FScopePythonGIL gil;

	py_uobject = ue_get_python_wrapper(this);
	if (!py_uobject) {
		unreal_engine_py_log_error();
		return;
	}

	PyObject *py_component_module = PyImport_ImportModule(TCHAR_TO_UTF8(*PythonModule));
	if (!py_component_module) {
		unreal_engine_py_log_error();
		return;
	}

#if WITH_EDITOR
	// todo implement autoreload with a dictionary of module timestamps
	py_component_module = PyImport_ReloadModule(py_component_module);
	if (!py_component_module) {
		unreal_engine_py_log_error();
		return;
	}
#endif

	if (PythonClass.IsEmpty())
		return;

	PyObject *py_component_module_dict = PyModule_GetDict(py_component_module);
	PyObject *py_component_class = PyDict_GetItemString(py_component_module_dict, TCHAR_TO_UTF8(*PythonClass));

	if (!py_component_class) {
		UE_LOG(LogPython, Error, TEXT("Unable to find class %s in module %s"), *PythonClass, *PythonModule);
		return;
	}

	py_component_instance = PyObject_CallObject(py_component_class, NULL);
	if (!py_component_instance) {
		unreal_engine_py_log_error();
		return;
	}

	py_uobject->py_proxy = py_component_instance;

	PyObject_SetAttrString(py_component_instance, (char *)"uobject", (PyObject *)py_uobject);


	// disable ticking if no tick method is exposed
	if (!PyObject_HasAttrString(py_component_instance, (char *)"tick") || PythonTickForceDisabled) {
		SetComponentTickEnabled(false);
	}

	if (!PythonDisableAutoBinding)
		ue_autobind_events_for_pyclass(py_uobject, py_component_instance);

	if (!PyObject_HasAttrString(py_component_instance, (char *)"begin_play")) {
		return;
	}

	PyObject *bp_ret = PyObject_CallMethod(py_component_instance, (char *)"begin_play", NULL);
	if (!bp_ret) {
		unreal_engine_py_log_error();
		return;
	}
	Py_DECREF(bp_ret);
}


// Called every frame
void UPythonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	// no need to check for method availability, we did it in begin_play

	PyObject *ret = PyObject_CallMethod(py_component_instance, (char *)"tick", (char *)"f", DeltaTime);
	if (!ret) {
		unreal_engine_py_log_error();
		return;
	}
	Py_DECREF(ret);

}

void UPythonComponent::CallPythonComponentMethod(FString method_name, FString args)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	PyObject *ret = nullptr;
	if (args.IsEmpty()) {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), NULL);
	}
	else {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), (char *)"s", TCHAR_TO_UTF8(*args));
	}

	if (!ret) {
		unreal_engine_py_log_error();
		return;
	}
	Py_DECREF(ret);
}

void UPythonComponent::SetPythonAttrObject(FString attr, UObject *object)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	ue_PyUObject *py_obj = ue_get_python_wrapper(object);
	if (!py_obj) {
		PyErr_Format(PyExc_Exception, "PyUObject is in invalid state");
		unreal_engine_py_log_error();
		return;
	}

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), (PyObject *)py_obj) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrString(FString attr, FString s)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), PyUnicode_FromString(TCHAR_TO_UTF8(*s))) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrFloat(FString attr, float f)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), PyFloat_FromDouble(f)) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrInt(FString attr, int n)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), PyLong_FromLong(n)) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrVector(FString attr, FVector vec)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), py_ue_new_fvector(vec)) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrRotator(FString attr, FRotator rot)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), py_ue_new_frotator(rot)) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

void UPythonComponent::SetPythonAttrBool(FString attr, bool b)
{
	if (!py_component_instance)
		return;

	FScopePythonGIL gil;

	PyObject *py_bool = Py_False;
	if (b) {
		py_bool = Py_True;
	}

	if (PyObject_SetAttrString(py_component_instance, TCHAR_TO_UTF8(*attr), py_bool) < 0) {
		UE_LOG(LogPython, Error, TEXT("Unable to set attribute %s"), *attr);
	}
}

bool UPythonComponent::CallPythonComponentMethodBool(FString method_name, FString args)
{
	if (!py_component_instance)
		return false;

	FScopePythonGIL gil;

	PyObject *ret = nullptr;
	if (args.IsEmpty()) {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), NULL);
	}
	else {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), (char *)"s", TCHAR_TO_UTF8(*args));
	}


	if (!ret) {
		unreal_engine_py_log_error();
		return false;
	}

	if (PyObject_IsTrue(ret)) {
		Py_DECREF(ret);
		return true;
	}

	Py_DECREF(ret);
	return false;
}

float UPythonComponent::CallPythonComponentMethodFloat(FString method_name, FString args)
{
	if (!py_component_instance)
		return false;

	FScopePythonGIL gil;

	PyObject *ret = nullptr;
	if (args.IsEmpty()) {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), NULL);
	}
	else {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), (char *)"s", TCHAR_TO_UTF8(*args));
	}


	if (!ret) {
		unreal_engine_py_log_error();
		return false;
	}

	float value = 0;

	if (PyNumber_Check(ret)) {
		PyObject *py_value = PyNumber_Float(ret);
		value = PyFloat_AsDouble(py_value);
		Py_DECREF(py_value);
	}

	Py_DECREF(ret);
	return value;
}

FString UPythonComponent::CallPythonComponentMethodString(FString method_name, FString args)
{
	if (!py_component_instance)
		return FString();

	FScopePythonGIL gil;

	PyObject *ret = nullptr;
	if (args.IsEmpty()) {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), NULL);
	}
	else {
		ret = PyObject_CallMethod(py_component_instance, TCHAR_TO_UTF8(*method_name), (char *)"s", TCHAR_TO_UTF8(*args));
	}

	if (!ret) {
		unreal_engine_py_log_error();
		return FString();
	}

	PyObject *py_str = PyObject_Str(ret);
	if (!py_str) {
		Py_DECREF(ret);
		return FString();
	}

	char *str_ret = PyUnicode_AsUTF8(py_str);

	FString ret_fstring = FString(UTF8_TO_TCHAR(str_ret));

	Py_DECREF(py_str);

	return ret_fstring;
}


UPythonComponent::~UPythonComponent()
{
	FScopePythonGIL gil;

	ue_pydelegates_cleanup(py_uobject);

#if UEPY_MEMORY_DEBUG
	if (py_component_instance && py_component_instance->ob_refcnt != 1) {
		UE_LOG(LogPython, Error, TEXT("Inconsistent Python UActorComponent wrapper refcnt = %d"), py_component_instance->ob_refcnt);
	}
#endif
	Py_XDECREF(py_component_instance);
	
#if UEPY_MEMORY_DEBUG
	UE_LOG(LogPython, Warning, TEXT("Python UActorComponent %p (mapped to %p) wrapper XDECREF'ed"), this, py_uobject ? py_uobject->ue_object : nullptr);
#endif

	// this could trigger the distruction of the python/uobject mapper
	Py_XDECREF(py_uobject);
}
