; ---------------------------------------------------------------------------- ;
; Example 3 - Calling Functions (Intermediate)
; ---------------------------------------------------------------------------- ;
; License: Creative Commons Attribution 2.0
; Author: Michael Fabian Dirks<michael.dirks@realitybends.de>
; Prerequisite: Example 2

; As said before, BlitzPointer offers one-thousand-three-hundred-sixty-four ways
;  of calling our function pointer. Each one describes return type, parameter 
;  count and parameter types. So, what magic can we do with those?

; There are four return types in Blitz that we can use:
; ---------------------------------------------------------------------------- ;
;  Type    Id  Description      Calling Function
; ---------------------------------------------------------------------------- ;
;   void	V	Nothing          BlitzPointer_CallFunctionV
;   int		I	32-bit Integer   BlitzPointer_CallFunctionI
;   float	F	Floating Point   BlitzPointer_CallFunctionF
;   string	S	String           BlitzPointer_CallFunctionS
;
; When returning strings we have to make sure that it is not 0-length, as Blitz
;  doesn't know how to handle these and crashes with a Memory Access Violation.

Include "Example_Shared.bb"
ExampleInit()

; 'void' function
Global fpVoidFunction = 0
Function VoidFunction()
	If fpVoidFunction = 0 Then
		fpVoidFunction = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	Text 0, 0, "Void Return Type"
End Function
VoidFunction()

Global fpIntFunction = 0
Function IntFunction%()
	If fpIntFunction = 0 Then
		fpIntFunction = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	Text   0, 15, "Int Return Type"
	Return MilliSecs()
End Function
IntFunction()

Global fpFloatFunction = 0
Function FloatFunction#()
	If fpFloatFunction = 0 Then
		fpFloatFunction = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	Text    0, 30, "Float Return Type"
	Return MilliSecs() / 1000.0
End Function
FloatFunction()

Global fpStringFunction = 0
Function StringFunction$()
	If fpStringFunction = 0 Then
		fpStringFunction = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	Text    0, 45, "String Return Type"
	
	Local T$ = ""
	Local MS = MilliSecs()
	T = (((MS / 1000) / 60) / 60) + ":" + RSet((((MS / 1000) / 60) Mod 60), 2) + ":" + RSet(((MS / 1000) Mod 60), 2) + "." + RSet(MS Mod 1000, 3)
	
	Return T
End Function
StringFunction()

While Not KeyHit(1)
	ExampleUpdate()
	
;	Calling the function and using the return value is really easy to do now:
	BlitzPointer_CallFunctionV(fpVoidFunction)		; void returns nothing.
	Text 200, 15, BlitzPointer_CallFunctionI(fpIntFunction)
	Text 200, 30, BlitzPointer_CallFunctionF(fpFloatFunction)
	Text 200, 45, BlitzPointer_CallFunctionS(fpStringFunction)
	
	ExampleLoop()
Wend
End
;~IDEal Editor Parameters:
;~C#Blitz3D