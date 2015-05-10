;----------------------------------------------------------------
;-- Vector2
;----------------------------------------------------------------
Type Vector2
	Field X#, Y#
End Type

Function Vector2_Create.Vector2(X#, Y#)
	Local vec.Vector2 = New Vector2
	vec\X = X
	vec\Y = Y
	Return vec
End Function

;----------------------------------------------------------------
;-- Vector3
;----------------------------------------------------------------
Type Vector3
	Field X#, Y#, Z#
End Type

Function Vector3_Create.Vector3(X#, Y#, Z#)
	Local vec.Vector3 = New Vector3
	vec\X = X
	vec\Y = Y
	vec\Z = Z
	Return vec
End Function

;----------------------------------------------------------------
;-- SQLite3
;----------------------------------------------------------------
;[Block] Return Codes / Error Codes
; Many SQLite functions return an integer result code from the set shown
; here in order to indicate success or failure.
;
; New error codes may be added in future versions of SQLite.
Const SQLITE_OK%			= 0   ; Successful result
Const SQLITE_ERROR%			= 1   ; SQL error or missing database
Const SQLITE_INTERNAL%		= 2   ; Internal logic error in SQLite
Const SQLITE_PERM%			= 3   ; Access permission denied
Const SQLITE_ABORT%			= 4   ; Callback routine requested an abort
Const SQLITE_BUSY%			= 5   ; The database file is locked
Const SQLITE_LOCKED%		= 6   ; A table in the database is locked
Const SQLITE_NOMEM%			= 7   ; A malloc() failed
Const SQLITE_READONLY%		= 8   ; Attempt to write a readonly database
Const SQLITE_INTERRUPT%		= 9   ; Operation terminated by SQLite3_Interrupt()
Const SQLITE_IOERR%			= 10   ; Some kind of disk I/O error occurred
Const SQLITE_CORRUPT%		= 11   ; The database disk image is malformed
Const SQLITE_NOTFOUND%		= 12   ; Unknown opcode in sqlite3_file_control()
Const SQLITE_FULL%			= 13   ; Insertion failed because database is full
Const SQLITE_CANTOPEN%		= 14   ; Unable to open the database file
Const SQLITE_PROTOCOL%		= 15   ; Database lock protocol error
Const SQLITE_EMPTY%			= 16   ; Database is empty
Const SQLITE_SCHEMA%		= 17   ; The database schema changed
Const SQLITE_TOOBIG%		= 18   ; String or BLOB exceeds size limit
Const SQLITE_CONSTRAINT%	= 19   ; Abort due to constraint violation
Const SQLITE_MISMATCH%		= 20   ; Data type mismatch
Const SQLITE_MISUSE%		= 21   ; Library used incorrectly
Const SQLITE_NOLFS%			= 22   ; Uses OS features not supported on host
Const SQLITE_AUTH%			= 23   ; Authorization denied
Const SQLITE_FORMAT%		= 24   ; Auxiliary database format error
Const SQLITE_RANGE%			= 25   ; 2nd parameter to sqlite3_bind out of range
Const SQLITE_NOTADB%		= 26   ; File opened that is not a database file
Const SQLITE_NOTICE%		= 27   ; Notifications from sqlite3_log()
Const SQLITE_WARNING%		= 28   ; Warnings from sqlite3_log()
Const SQLITE_ROW%			= 100  ; sqlite3_step() has another row ready
Const SQLITE_DONE%			= 101  ; sqlite3_step() has finished executing
;[End Block]

;[Block] SQLite_Open Flags
; These bit values are intended for use in the
; 3rd parameter to the [sqlite3_open_v2()] interface.
Const SQLITE_OPEN_READONLY%		= $00000001
Const SQLITE_OPEN_READWRITE%	= $00000002
Const SQLITE_OPEN_CREATE%		= $00000004
Const SQLITE_OPEN_URI%			= $00000040
Const SQLITE_OPEN_MEMORY%		= $00000080
Const SQLITE_OPEN_NOMUTEX%		= $00008000
Const SQLITE_OPEN_FULLMUTEX%	= $00010000
Const SQLITE_OPEN_SHAREDCACHE%	= $00020000
Const SQLITE_OPEN_PRIVATECACHE%	= $00040000
;[End Block]

;[Block] Column Type
Const SQLITE_UNKNOWN	= 0
Const SQLITE_INTEGER	= 1
Const SQLITE_REAL		= 2
Const SQLITE_FLOAT		= 2
Const SQLITE_DOUBLE		= 2
Const SQLITE_TEXT		= 3
Const SQLITE_STRING		= 3
Const SQLITE_BLOB		= 4
Const SQLITE_NULL		= 5
;[End Block]

;[Block] Internal Types
Type SQLite_Container
	Field Pointer%
End Type

Type SQLite_Int64
	Field Left%, Right%
End Type
;[End Block]

Function SQLite_Open%(File$, Flags% = $00000006)
	; Create a Container to hold the database pointer.
	Local Container.SQLite_Container = New SQLite_Container
	Local ErrCode = SQLite3_Open_V2(File, Container, Flags, 0)
	Local Database = Container\Pointer
	Delete Container
	
	If ErrCode = SQLITE_OK
		Return Database
	Else
		Return False
	EndIf
End Function

Function SQLite_Execute(Database, SQL$)
	Return SQLite3_Exec(Database, SQL, 0, 0, 0)
End Function

Function SQLite_Prepare(Database, SQL$)
	Local Container.SQLite_Container = New SQLite_Container
	Local ErrCode = SQLite3_Prepare(Database, SQL$, -1, Container, 0)
	Local Statement = Container\Pointer
	Delete Container
	
	If ErrCode = SQLITE_OK
		Return Statement
	Else
		Return False
	EndIf
End Function

Global SQLite_Column_Int64_L%, SQLite_Column_Int64_R%
Function SQLite_Column_Int64(Statement, ColumnIndex%)
	Local Result.SQLite_Int64 = New SQLite_Int64
	SQLite3_Column_Int64(Statement, ColumnIndex, Result)
	SQLite_Column_Int64_L = Result\Left
	SQLite_Column_Int64_R = Result\Right
	Delete Result
End Function

Function SQLite_Bind_Text(Statement, ColumnIndex%, Value$)
	Return SQLite3_Bind_Text(Statement, ColumnIndex, Value, -1, -1)
End Function

Function SQLite_Bind_Blob(Statement, ColumnIndex%, Bank)
	If Bank <> 0 Then
		Local Size% = BankSize(Bank)
		Return SQLite3_Bind_Blob(Statement, ColumnIndex, Bank, Size, 0)
	EndIf
End Function

;----------------------------------------------------------------
;-- Helpers
;----------------------------------------------------------------
Type BlitzUtility_Rectangle
	Field X,Y,X2,Y2
End Type

Type BlitzUtility_Point
	Field X,Y
End Type

Global BlitzUtility_Rect.BlitzUtility_Rectangle = New BlitzUtility_Rectangle
Global BlitzUtility_Point.BlitzUtility_Point = New BlitzUtility_Point

Function BlitzUtility_LockPointerToWindow(hwnd=0)
	If hwnd = 0 Then
		BlitzUtility_User32_ClipCursorI(0)
	Else
		BlitzUtility_User32_GetWindowRect(hwnd, BlitzUtility_Rect)

		;Grab TopLeft
		BlitzUtility_Point\X = BlitzUtility_Rect\X
		BlitzUtility_Point\Y = BlitzUtility_Rect\Y
		BlitzUtility_Rect\X = BlitzUtility_Point\X
		BlitzUtility_Rect\Y = BlitzUtility_Point\Y
		
		;Grab BottomRight
		BlitzUtility_Point\X = BlitzUtility_Rect\X2 - 1
		BlitzUtility_Point\Y = BlitzUtility_Rect\Y2 - 1
		BlitzUtility_Rect\X2 = BlitzUtility_Point\X
		BlitzUtility_Rect\Y2 = BlitzUtility_Point\Y
		
		BlitzUtility_User32_ClipCursor(BlitzUtility_Rect)
	EndIf
End Function

Function BlitzUtility_LockPointerToWindowAuto(hwnd=0)
	If BlitzUtility_User32_GetActiveWindow() = hwnd Then
		BlitzUtility_LockPointerToWindow(hwnd)
	Else
		BlitzUtility_LockPointerToWindow(0)
	EndIf
End Function

Function BlitzUtility_BorderlessWindowmode(hwnd=0, MonitorId=0, Width=0, Height=0)
	If hwnd = 0 Then hwnd = SystemProperty("AppHwnd")
	
	BlitzUtility_EnumerateDisplays()
	Local dispCnt = BlitzUtility_GetDisplayCount()
	If MonitorId < 0 Then MonitorId = 0
	If MonitorId >= dispCnt Then MonitorId = dispCnt - 1
	
	Local rct.BlitzUtility_Rectangle = New BlitzUtility_Rectangle
	BlitzUtility_GetDisplay(MonitorId, rct)
	Local rctW, rctH
	rctW = (rct\X2 - rct\X)
	rctH = (rct\Y2 - rct\Y)
	
	
	rct\X = rct\X + (rctW / 2.0) - Width / 2.0
	rct\Y = rct\Y + (rctH / 2.0) - Height / 2.0
	rct\X2 = Width
	rct\Y2 = Height
	BlitzUtility_User32_SetWindowLong hwnd, -16, $01000000
	BlitzUtility_User32_SetWindowPos hwnd, 0, rct\X, rct\Y, rct\X2, rct\Y2, 64
	Delete rct
End Function

Function FlushFile(File%)
	Return BlitzUtility_Kernel32_FlushFileBuffers(File)
End Function

;~IDEal Editor Parameters:
;~F#20#46#54
;~C#Blitz3D