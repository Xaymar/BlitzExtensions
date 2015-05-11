; ---------------------------------------------------------------------------- ;
; Example 4 - Callbacks
; ---------------------------------------------------------------------------- ;
; License: Creative Commons Attribution 2.0
; Author: Michael Fabian Dirks<michael.dirks@realitybends.de>
; Prerequisite: Example 4

; Now that we have learned how to use functions, let's go for something really
;  advanced - Callbacks! We can use these to practically fake a OOP language.

Include "Example_Shared.bb"
ExampleInit()

; Let's create a Type to hold our generic object that only contains callback and
;  a pointer to the type object. This allows us to have a generic interface that
;  takes BObject and whatever type-object the user wants and returns weether or
;  not the BObject should be destroyed.
Type BObject
	Field DataCallback
	Field DataValue%
End Type

; Our Update loop looks like this, there's not much to do - after all we have
;  the callbacks to do the dirty work for us.
Function BObjectUpdate()
	Local Obj.BObject
	For Obj.BObject = Each BObject
		; Check if the Callback and Value is set.
		If Obj\DataCallback <> 0 And Obj\DataValue <> 0 Then
			; Our Callback tells us when we need to dispose of an object.
			If BlitzPointer_CallFunctionIII(Obj\DataCallback, Int(Obj), Obj\DataValue)
				Delete Obj
			EndIf
		Else
			Delete Obj
		EndIf
	Next
End Function

; We'll have two different sub-objects:
; * BCube - Cubes with movement
; * BSphere - Randomly colored spheres

; BCube - Spawned when we press '1'
Type BCube
	Field Entity
	Field PosX#, PosY#, PosZ#
	Field Time
End Type

; Our Callback for BCube - relatively simple.
Global fpBCubeCallback = 0
Function BCubeCallback%(Obj.BObject, Cube.BCube)
	If fpBCubeCallback = 0 Then
		fpBCubeCallback = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	
	Local Prc# = 1.0 - ((MilliSecs() - Cube\Time) / 5000.0)
	PositionEntity Cube\Entity, Cube\PosX, Cos(Cube\PosX + Prc * 360) * Sin(Cos(Cube\PosZ) * 180 + Prc * 360) * 50, Cube\PosZ
	EntityAlpha Cube\Entity, Prc
	
	If Prc < 0.0 Then
		FreeEntity Cube\Entity
		Delete Cube
		Return True
	EndIf
	Return False
End Function
BCubeCallback(Null, Null)

Function BCubeCreate.BObject(X#, Y#, Z#)
	Local Obj.BObject = New BObject
	Obj\DataCallback = fpBCubeCallback
	Local Cube.BCube = New BCube
	Cube\Entity = CreateCube()
	Cube\PosX = X
	Cube\PosY = Y
	Cube\PosZ = Z
	Cube\Time = MilliSecs()
	Obj\DataValue = Int(Cube)
	
	Return Obj
End Function

; Our BSphere implementation, spawned when pressing 2
Type BSphere
	Field Entity
	Field StartColor[2]
	Field EndColor[2]
	Field Time
End Type

Global fpBSphereCallback = 0
Function BSphereCallback%(Obj.BObject, Sphere.BSphere)
	If fpBSphereCallback = 0 Then
		fpBSphereCallback = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	
	Local Prc# = (MilliSecs() - Sphere\Time) / 5000.0
	EntityColor Sphere\Entity, Sphere\StartColor[0] * (1.0 - Prc) + Sphere\EndColor[0] * Prc, Sphere\StartColor[1] * (1.0 - Prc) + Sphere\EndColor[1] * Prc, Sphere\StartColor[2] * (1.0 - Prc) + Sphere\EndColor[2] * Prc
	EntityAlpha Sphere\Entity, 1.0 - Prc
	If Prc >= 1.0 Then
		FreeEntity Sphere\Entity
		Delete Sphere
		Return True
	EndIf
	Return False
End Function
BSphereCallback(Null, Null)

Function BSphereCreate.BObject(X#, Y#, Z#)
	Local Obj.BObject = New BObject
	Obj\DataCallback = fpBSphereCallback
	Local Sphere.BSphere = New BSphere
	Sphere\Entity = CreateSphere(2)
	PositionEntity Sphere\Entity, X, Y, Z
	Sphere\StartColor[0] = Rand(0, 255)
	Sphere\StartColor[1] = Rand(0, 255)
	Sphere\StartColor[2] = Rand(0, 255)
	Sphere\EndColor[0] = Rand(0, 255)
	Sphere\EndColor[1] = Rand(0, 255)
	Sphere\EndColor[2] = Rand(0, 255)
	Sphere\Time = MilliSecs()
	Obj\DataValue = Int(Sphere)
	Return Obj
End Function

SeedRnd MilliSecs()

While Not KeyHit(1)
	;'1' spawns a few instances of BCube
	If KeyHit(2) Then
		For X = -100 To 100 Step 10
			For Z = -100 To 100 Step 10
				BCubeCreate(X, 0, Z)
			Next
		Next
	EndIf
	
	;'2' spawns a few instances of BSphere
	If KeyHit(3) Then
		Local O# = Rnd(-360, 360)
		For R# = -180 To 180 Step 2.25
			BSphereCreate(Cos(R+O)*100, Sin(R * 90) * 10 + 10, Sin(R+O)*100)
		Next
	EndIf
	
	
	; We only need one function here, all other updates are done using callbacks.
	BObjectUpdate()
	
	ExampleUpdate()
	ExampleLoop()
Wend
;~IDEal Editor Parameters:
;~C#Blitz3D