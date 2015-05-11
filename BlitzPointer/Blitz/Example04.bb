; ---------------------------------------------------------------------------- ;
; Example 4 - Calling Functions (Advanced)
; ---------------------------------------------------------------------------- ;
; License: Creative Commons Attribution 2.0
; Author: Michael Fabian Dirks<michael.dirks@realitybends.de>
; Prerequisite: Example 3

; We now know how to use return values correctly and thus have knowledge about
;  the first 4 of 1364 functions to call a pointer.
;  Now you know about 4 different ways of calling a Function, what about the 
;  other 1360 that are left? Those are combinations of return types, parameter
;  count and parameter types.
; BlitzPointer supports functions with up to four parameters, given that all
;  parameters have a supported type.

; There are three parameter types in Blitz that we can use:
; ---------------------------------------------------------------------------- ;
;  Type    Id  Description      Calling Function
; ---------------------------------------------------------------------------- ;
;   int     I   32-bit Integer   BlitzPointer_CallFunction*I
;   float   F   Floating Point   BlitzPointer_CallFunction*F
;   type    I   Type Object      BlitzPointer_CallFunction*I
;   pointer P   Memory Pointer   BlitzPointer_CallFunction*P
; 
; We can't pass strings as parameters, but we can pass types as parameters,
;  which allows us to pass strings in a type.

Include "Example_Shared.bb"
ExampleInit()

; Example Function: Divide p1 by 60 and return the result.
Global fpCurInGameSecond = 0
Function CurInGameSecond%(p1%=0)
	If fpCurInGameSecond = 0 Then
		fpCurInGameSecond = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	Text   5, 15, "IIFunction"
	Text 125, 15, p1
	
	Return (p1 Shr 2) / 15 ; Division by 60
End Function
CurInGameSecond()

; Example Function: Multiply p1 by p2 and return the result.
Global fpCurInGameSecondEx = 0
Function CurInGameSecondEx#(p1%=0, p2#=0)
	If fpCurInGameSecondEx = 0 Then
		fpCurInGameSecondEx = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	
	Text   5, 30, "FIFFunction"
	Text 125, 30, p1
	Text 245, 30, p2
	
	Return p1 * p2
End Function
CurInGameSecondEx()

; Example Function: Work around the fact that Strings can't be passed.
Type MyType
	Field Name$
	Field Desc$
End Type
Local MT.MyType = New MyType
MT\Name = "Hello"
MT\Desc = "World"

Global fpDisplayMyType = 0
Function DisplayMyType(p1.MyType)
	If fpDisplayMyType = 0 Then
		fpDisplayMyType = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	
	Text   5, 45, "VTFunction"
	Text 125, 45, Hex(Int(p1))
	If p1 <> Null Then
		Text 245, 45, p1\Name
		Text 365, 45, p1\Desc
	EndIf
End Function
DisplayMyType(Null)

; Example Function: Convert between Float and Int easily
;  For this to work we must take and return a float.
Global fpConvertIntFloat
Function ConvertIntFloat#(p1#=0)
	If fpConvertIntFloat = 0 Then
		fpConvertIntFloat = BlitzPointer_GetFunctionPointer()
		Return
	EndIf
	
	Return p1
End Function
ConvertIntFloat()

; Pointer-parameters are a bit trickier and require memory access, see UserLibs.txt.

Local Frame% = 0
While Not KeyHit(1)
	ExampleUpdate()
	
	Text   0, 0, "Functions"
	Text 120, 0, "Parameter 1"
	Text 240, 0, "Parameter 2"
	Text 360, 0, "Parameter 3"
	Text 480, 0, "Parameter 4"
	Text 600, 0, "Result"
	
	Text 605, 15, BlitzPointer_CallFunctionII(fpCurInGameSecond, Frame)
	Text 605, 30, BlitzPointer_CallFunctionFIF(fpCurInGameSecondEx, Frame, 0.016666666)
;   In order to pass a Type-object to a function, we need to get a pointer for it.
;   Thankfully, Blitz can do this natively by calling Int() on it.
	BlitzPointer_CallFunctionVI fpDisplayMyType, Int(MT)
	
	Local TempFlt# = Frame / 60.0
	Local TempInt% = BlitzPointer_CallFunctionIF(fpConvertIntFloat, TempFlt)
	Text   5, 60, "Float -> Int"
	Text 125, 60, TempFlt
	Text 605, 60, Hex(TempInt)
	
	Text   5, 75, "Int -> Float"
	Text 125, 75, Hex(TempInt)
	Text 605, 75, BlitzPointer_CallFunctionFI(fpConvertIntFloat, TempInt)
	
	ExampleLoop()
	
	; Allow us to pause execution
	While KeyDown(57)
		WaitTimer(Example_Timer)
	Wend
	
	Frame=Frame+1
Wend
End
;~IDEal Editor Parameters:
;~C#Blitz3D