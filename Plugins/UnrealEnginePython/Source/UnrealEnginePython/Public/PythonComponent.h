#pragma once

#include "Components/ActorComponent.h"

#include "PythonComponent.generated.h"



UCLASS(ClassGroup = (Python), meta = (BlueprintSpawnableComponent))
class UPythonComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPythonComponent();
	~UPythonComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere , Category = "Python")
	FString PythonModule;

	UPROPERTY(EditAnywhere, Category = "Python")
	FString PythonClass;

	UPROPERTY(EditAnywhere, Category = "Python")
	bool PythonTickForceDisabled;

	UPROPERTY(EditAnywhere, Category = "Python")
	bool PythonDisableAutoBinding;

	UFUNCTION(BlueprintCallable, Category = "Python")
	void CallPythonComponentMethod(FString method_name, FString args);

	UFUNCTION(BlueprintCallable, Category = "Python")
	bool CallPythonComponentMethodBool(FString method_name, FString args);

	UFUNCTION(BlueprintCallable, Category = "Python")
	FString CallPythonComponentMethodString(FString method_name, FString args);

	UFUNCTION(BlueprintCallable, Category = "Python")
	float CallPythonComponentMethodFloat(FString method_name, FString args);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrInt(FString attr, int Integer);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrFloat(FString attr, float Float);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrString(FString attr, FString String);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrBool(FString attr, bool Boolean);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrVector(FString attr, FVector Vector);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrRotator(FString attr, FRotator Rotator);

	UFUNCTION(BlueprintCallable, Category = "Python")
	void SetPythonAttrObject(FString attr, UObject *Object);

private:
	PyObject *py_component_instance;
	// mapped uobject, required for debug and advanced reflection
	ue_PyUObject *py_uobject;
};

