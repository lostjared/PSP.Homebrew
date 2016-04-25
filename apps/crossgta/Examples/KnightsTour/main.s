	.file	1 "main.c"
	.section .mdebug.eabi32
	.section .gcc_compiled_long32
	.previous
	.globl	vertical
	.data
	.align	2
	.type	vertical, @object
	.size	vertical, 32
vertical:
	.word	-1
	.word	-2
	.word	-2
	.word	-1
	.word	1
	.word	2
	.word	2
	.word	1
	.globl	horizontal
	.align	2
	.type	horizontal, @object
	.size	horizontal, 32
horizontal:
	.word	2
	.word	1
	.word	-1
	.word	-2
	.word	-2
	.word	-1
	.word	1
	.word	2
	.globl	htable
	.align	2
	.type	htable, @object
	.size	htable, 256
htable:
	.word	2
	.word	3
	.word	4
	.word	4
	.word	4
	.word	4
	.word	3
	.word	2
	.word	3
	.word	4
	.word	6
	.word	6
	.word	6
	.word	6
	.word	4
	.word	3
	.word	4
	.word	6
	.word	8
	.word	8
	.word	8
	.word	8
	.word	6
	.word	4
	.word	4
	.word	6
	.word	8
	.word	8
	.word	8
	.word	8
	.word	6
	.word	4
	.word	4
	.word	6
	.word	8
	.word	8
	.word	8
	.word	8
	.word	6
	.word	4
	.word	4
	.word	6
	.word	8
	.word	8
	.word	8
	.word	8
	.word	6
	.word	4
	.word	3
	.word	4
	.word	6
	.word	6
	.word	6
	.word	6
	.word	4
	.word	3
	.word	2
	.word	3
	.word	4
	.word	4
	.word	4
	.word	4
	.word	3
	.word	2
	.globl	starty
	.align	2
	.type	starty, @object
	.size	starty, 4
starty:
	.word	50
	.globl	startx
	.align	2
	.type	startx, @object
	.size	startx, 4
startx:
	.word	50
	.globl	moves
	.section	.bss,"aw",@nobits
	.align	2
	.type	moves, @object
	.size	moves, 4
moves:
	.space	4
	.globl	numfailed
	.align	2
	.type	numfailed, @object
	.size	numfailed, 4
numfailed:
	.space	4
	.globl	hash_values
	.data
	.align	2
	.type	hash_values, @object
	.size	hash_values, 20
hash_values:
	.byte	-37
	.byte	-84
	.byte	50
	.byte	-42
	.byte	60
	.byte	89
	.byte	-24
	.byte	-50
	.byte	-89
	.byte	115
	.byte	29
	.byte	-16
	.byte	108
	.byte	39
	.byte	124
	.byte	15
	.byte	-105
	.byte	-58
	.byte	12
	.byte	-49
	.globl	functions
	.align	2
	.type	functions, @object
	.size	functions, 640
functions:
	.word	278876348
	.word	sceIoOpen
	.word	IoFileMgrForUser
	.word	0
	.word	-2129900605
	.word	sceIoClose
	.word	IoFileMgrForUser
	.word	0
	.word	1784909187
	.word	sceIoRead
	.word	IoFileMgrForUser
	.word	0
	.word	1122763692
	.word	sceIoWrite
	.word	IoFileMgrForUser
	.word	0
	.word	772346282
	.word	sceKernelUnloadModule
	.word	ModuleMgrForUser
	.word	0
	.word	-771778518
	.word	sceKernelStopModule
	.word	ModuleMgrForUser
	.word	0
	.word	-696915016
	.word	sceKernelSelfStopUnloadModule
	.word	ModuleMgrForUser
	.word	0
	.word	595443023
	.word	sceKernelAllocPartitionMemory
	.word	SysMem
	.word	0
	.word	-1227481854
	.word	sceKernelFreePartitionMemory
	.word	SysMem
	.word	0
	.word	-1650828383
	.word	sceKernelGetBlockHeadAddr
	.word	SysMem
	.word	0
	.word	-1567493881
	.word	sceKernelMaxFreeMemSize
	.word	SysMem
	.word	0
	.word	943684556
	.word	sceKernelTerminateDeleteThread
	.word	Threadman
	.word	0
	.word	691750328
	.word	sceKernelGetThreadId
	.word	Threadman
	.word	0
	.word	1148030438
	.word	sceKernelCreateThread
	.word	Threadman
	.word	0
	.word	-193624995
	.word	sceKernelStartThread
	.word	Threadman
	.word	0
	.word	-827462841
	.word	sceKernelDelayThread
	.word	Threadman
	.word	0
	.word	-306554812
	.word	sceKernelDeleteCallback
	.word	Threadman
	.word	0
	.word	-317452064
	.word	sceKernelDeleteFpl
	.word	Threadman
	.word	0
	.word	683034780
	.word	sceKernelDeleteSema
	.word	Threadman
	.word	0
	.word	-702650015
	.word	sceKernelReleaseSubIntrHandler
	.word	InterruptManager
	.word	0
	.word	-905665863
	.word	0
	.word	InterruptManager
	.word	0
	.word	-74571028
	.word	0
	.word	InterruptManager
	.word	0
	.word	-1271537979
	.word	sceKernelDcacheWritebackInvalidateAll
	.word	UtilsForUser
	.word	0
	.word	1911308913
	.word	sceKernelLibcGettimeofday
	.word	UtilsForUser
	.word	0
	.word	-1519786971
	.word	sceKernelVolatileMemUnlock
	.word	SuspendForUser
	.word	0
	.word	-1121198585
	.word	sceUmdUnRegisterUMDCallBack
	.word	UMDForUser
	.word	0
	.word	-542590216
	.word	scePowerUnregisterCallback
	.word	Power
	.word	0
	.word	98247374
	.word	sceGeUnsetCallback
	.word	ge
	.word	0
	.word	-1752124612
	.word	sceUtilitySavedataShutdownStart
	.word	sceUtility
	.word	0
	.word	-726048773
	.word	sceUtilitySavedataUpdate
	.word	sceUtility
	.word	0
	.word	-2005607456
	.word	sceUtilitySavedataGetStatus
	.word	sceUtility
	.word	0
	.word	1780970739
	.word	sceCtrlSetSamplingCycle
	.word	sceCtrl
	.word	0
	.word	524292582
	.word	sceCtrlSetSamplingMode
	.word	sceCtrl
	.word	0
	.word	528496952
	.word	sceCtrlReadBufferPositive
	.word	sceCtrl
	.word	0
	.word	-1739839513
	.word	sceDisplayWaitVblankStart
	.word	sceDisplay
	.word	0
	.word	237039991
	.word	sceDisplaySetMode
	.word	sceDisplay
	.word	0
	.word	681411326
	.word	sceDisplaySetFrameBuf
	.word	sceDisplay
	.word	0
	.word	1875142739
	.word	sceAudioChRelease
	.word	sceAudio
	.word	0
	.word	89598559
	.word	sceKernelExitGame
	.word	LoadExecForUser
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.globl	LoadExecForUser
	.align	2
	.type	LoadExecForUser, @object
	.size	LoadExecForUser, 16
LoadExecForUser:
	.ascii	"LoadExecForUser\000"
	.globl	sceUtility
	.align	2
	.type	sceUtility, @object
	.size	sceUtility, 11
sceUtility:
	.ascii	"sceUtility\000"
	.globl	sceAudio
	.align	2
	.type	sceAudio, @object
	.size	sceAudio, 9
sceAudio:
	.ascii	"sceAudio\000"
	.globl	Power
	.align	2
	.type	Power, @object
	.size	Power, 9
Power:
	.ascii	"scePower\000"
	.globl	UMDForUser
	.align	2
	.type	UMDForUser, @object
	.size	UMDForUser, 11
UMDForUser:
	.ascii	"sceUmdUser\000"
	.globl	SuspendForUser
	.align	2
	.type	SuspendForUser, @object
	.size	SuspendForUser, 18
SuspendForUser:
	.ascii	"sceSuspendForUser\000"
	.globl	ModuleMgrForUser
	.align	2
	.type	ModuleMgrForUser, @object
	.size	ModuleMgrForUser, 17
ModuleMgrForUser:
	.ascii	"ModuleMgrForUser\000"
	.globl	InterruptManager
	.align	2
	.type	InterruptManager, @object
	.size	InterruptManager, 17
InterruptManager:
	.ascii	"InterruptManager\000"
	.globl	UtilsForUser
	.align	2
	.type	UtilsForUser, @object
	.size	UtilsForUser, 13
UtilsForUser:
	.ascii	"UtilsForUser\000"
	.globl	ge
	.align	2
	.type	ge, @object
	.size	ge, 11
ge:
	.ascii	"sceGe_user\000"
	.globl	SysMem
	.align	2
	.type	SysMem, @object
	.size	SysMem, 18
SysMem:
	.ascii	"SysMemUserForUser\000"
	.globl	sceCtrl
	.align	2
	.type	sceCtrl, @object
	.size	sceCtrl, 8
sceCtrl:
	.ascii	"sceCtrl\000"
	.globl	sceDisplay
	.align	2
	.type	sceDisplay, @object
	.size	sceDisplay, 11
sceDisplay:
	.ascii	"sceDisplay\000"
	.globl	Threadman
	.align	2
	.type	Threadman, @object
	.size	Threadman, 17
Threadman:
	.ascii	"ThreadManForUser\000"
	.globl	IoFileMgrForUser
	.align	2
	.type	IoFileMgrForUser, @object
	.size	IoFileMgrForUser, 17
IoFileMgrForUser:
	.ascii	"IoFileMgrForUser\000"
	.globl	vramtop
	.align	2
	.type	vramtop, @object
	.size	vramtop, 4
vramtop:
	.word	67108864
	.globl	font
	.rdata
	.align	2
	.type	font, @object
	.size	font, 2048
font:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	120
	.byte	120
	.byte	48
	.byte	48
	.byte	0
	.byte	48
	.byte	0
	.byte	108
	.byte	108
	.byte	108
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	108
	.byte	108
	.byte	-2
	.byte	108
	.byte	-2
	.byte	108
	.byte	108
	.byte	0
	.byte	48
	.byte	124
	.byte	-64
	.byte	120
	.byte	12
	.byte	-8
	.byte	48
	.byte	0
	.byte	0
	.byte	-58
	.byte	-52
	.byte	24
	.byte	48
	.byte	102
	.byte	-58
	.byte	0
	.byte	56
	.byte	108
	.byte	56
	.byte	118
	.byte	-36
	.byte	-52
	.byte	118
	.byte	0
	.byte	96
	.byte	96
	.byte	-64
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	48
	.byte	96
	.byte	96
	.byte	96
	.byte	48
	.byte	24
	.byte	0
	.byte	96
	.byte	48
	.byte	24
	.byte	24
	.byte	24
	.byte	48
	.byte	96
	.byte	0
	.byte	0
	.byte	102
	.byte	60
	.byte	-1
	.byte	60
	.byte	102
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	-4
	.byte	48
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	96
	.byte	0
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	0
	.byte	6
	.byte	12
	.byte	24
	.byte	48
	.byte	96
	.byte	-64
	.byte	-128
	.byte	0
	.byte	124
	.byte	-58
	.byte	-50
	.byte	-34
	.byte	-10
	.byte	-26
	.byte	124
	.byte	0
	.byte	48
	.byte	112
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	-4
	.byte	0
	.byte	120
	.byte	-52
	.byte	12
	.byte	56
	.byte	96
	.byte	-52
	.byte	-4
	.byte	0
	.byte	120
	.byte	-52
	.byte	12
	.byte	56
	.byte	12
	.byte	-52
	.byte	120
	.byte	0
	.byte	28
	.byte	60
	.byte	108
	.byte	-52
	.byte	-2
	.byte	12
	.byte	30
	.byte	0
	.byte	-4
	.byte	-64
	.byte	-8
	.byte	12
	.byte	12
	.byte	-52
	.byte	120
	.byte	0
	.byte	56
	.byte	96
	.byte	-64
	.byte	-8
	.byte	-52
	.byte	-52
	.byte	120
	.byte	0
	.byte	-4
	.byte	-52
	.byte	12
	.byte	24
	.byte	48
	.byte	48
	.byte	48
	.byte	0
	.byte	120
	.byte	-52
	.byte	-52
	.byte	120
	.byte	-52
	.byte	-52
	.byte	120
	.byte	0
	.byte	120
	.byte	-52
	.byte	-52
	.byte	124
	.byte	12
	.byte	24
	.byte	112
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	0
	.byte	0
	.byte	48
	.byte	48
	.byte	96
	.byte	24
	.byte	48
	.byte	96
	.byte	-64
	.byte	96
	.byte	48
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	96
	.byte	48
	.byte	24
	.byte	12
	.byte	24
	.byte	48
	.byte	96
	.byte	0
	.byte	120
	.byte	-52
	.byte	12
	.byte	24
	.byte	48
	.byte	0
	.byte	48
	.byte	0
	.byte	124
	.byte	-58
	.byte	-34
	.byte	-34
	.byte	-34
	.byte	-64
	.byte	120
	.byte	0
	.byte	48
	.byte	120
	.byte	-52
	.byte	-52
	.byte	-4
	.byte	-52
	.byte	-52
	.byte	0
	.byte	-4
	.byte	102
	.byte	102
	.byte	124
	.byte	102
	.byte	102
	.byte	-4
	.byte	0
	.byte	60
	.byte	102
	.byte	-64
	.byte	-64
	.byte	-64
	.byte	102
	.byte	60
	.byte	0
	.byte	-8
	.byte	108
	.byte	102
	.byte	102
	.byte	102
	.byte	108
	.byte	-8
	.byte	0
	.byte	-2
	.byte	98
	.byte	104
	.byte	120
	.byte	104
	.byte	98
	.byte	-2
	.byte	0
	.byte	-2
	.byte	98
	.byte	104
	.byte	120
	.byte	104
	.byte	96
	.byte	-16
	.byte	0
	.byte	60
	.byte	102
	.byte	-64
	.byte	-64
	.byte	-50
	.byte	102
	.byte	62
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-4
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	0
	.byte	120
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	120
	.byte	0
	.byte	30
	.byte	12
	.byte	12
	.byte	12
	.byte	-52
	.byte	-52
	.byte	120
	.byte	0
	.byte	-26
	.byte	102
	.byte	108
	.byte	120
	.byte	108
	.byte	102
	.byte	-26
	.byte	0
	.byte	-16
	.byte	96
	.byte	96
	.byte	96
	.byte	98
	.byte	102
	.byte	-2
	.byte	0
	.byte	-58
	.byte	-18
	.byte	-2
	.byte	-2
	.byte	-42
	.byte	-58
	.byte	-58
	.byte	0
	.byte	-58
	.byte	-26
	.byte	-10
	.byte	-34
	.byte	-50
	.byte	-58
	.byte	-58
	.byte	0
	.byte	56
	.byte	108
	.byte	-58
	.byte	-58
	.byte	-58
	.byte	108
	.byte	56
	.byte	0
	.byte	-4
	.byte	102
	.byte	102
	.byte	124
	.byte	96
	.byte	96
	.byte	-16
	.byte	0
	.byte	120
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-36
	.byte	120
	.byte	28
	.byte	0
	.byte	-4
	.byte	102
	.byte	102
	.byte	124
	.byte	108
	.byte	102
	.byte	-26
	.byte	0
	.byte	120
	.byte	-52
	.byte	-32
	.byte	112
	.byte	28
	.byte	-52
	.byte	120
	.byte	0
	.byte	-4
	.byte	-76
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	120
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-4
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	120
	.byte	48
	.byte	0
	.byte	-58
	.byte	-58
	.byte	-58
	.byte	-42
	.byte	-2
	.byte	-18
	.byte	-58
	.byte	0
	.byte	-58
	.byte	-58
	.byte	108
	.byte	56
	.byte	56
	.byte	108
	.byte	-58
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	120
	.byte	48
	.byte	48
	.byte	120
	.byte	0
	.byte	-2
	.byte	-58
	.byte	-116
	.byte	24
	.byte	50
	.byte	102
	.byte	-2
	.byte	0
	.byte	120
	.byte	96
	.byte	96
	.byte	96
	.byte	96
	.byte	96
	.byte	120
	.byte	0
	.byte	-64
	.byte	96
	.byte	48
	.byte	24
	.byte	12
	.byte	6
	.byte	2
	.byte	0
	.byte	120
	.byte	24
	.byte	24
	.byte	24
	.byte	24
	.byte	24
	.byte	120
	.byte	0
	.byte	16
	.byte	56
	.byte	108
	.byte	-58
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-1
	.byte	48
	.byte	48
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	120
	.byte	12
	.byte	124
	.byte	-52
	.byte	118
	.byte	0
	.byte	-32
	.byte	96
	.byte	96
	.byte	124
	.byte	102
	.byte	102
	.byte	-36
	.byte	0
	.byte	0
	.byte	0
	.byte	120
	.byte	-52
	.byte	-64
	.byte	-52
	.byte	120
	.byte	0
	.byte	28
	.byte	12
	.byte	12
	.byte	124
	.byte	-52
	.byte	-52
	.byte	118
	.byte	0
	.byte	0
	.byte	0
	.byte	120
	.byte	-52
	.byte	-4
	.byte	-64
	.byte	120
	.byte	0
	.byte	56
	.byte	108
	.byte	96
	.byte	-16
	.byte	96
	.byte	96
	.byte	-16
	.byte	0
	.byte	0
	.byte	0
	.byte	118
	.byte	-52
	.byte	-52
	.byte	124
	.byte	12
	.byte	-8
	.byte	-32
	.byte	96
	.byte	108
	.byte	118
	.byte	102
	.byte	102
	.byte	-26
	.byte	0
	.byte	48
	.byte	0
	.byte	112
	.byte	48
	.byte	48
	.byte	48
	.byte	120
	.byte	0
	.byte	12
	.byte	0
	.byte	12
	.byte	12
	.byte	12
	.byte	-52
	.byte	-52
	.byte	120
	.byte	-32
	.byte	96
	.byte	102
	.byte	108
	.byte	120
	.byte	108
	.byte	-26
	.byte	0
	.byte	112
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	120
	.byte	0
	.byte	0
	.byte	0
	.byte	-52
	.byte	-2
	.byte	-2
	.byte	-42
	.byte	-58
	.byte	0
	.byte	0
	.byte	0
	.byte	-8
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	0
	.byte	0
	.byte	0
	.byte	120
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	120
	.byte	0
	.byte	0
	.byte	0
	.byte	-36
	.byte	102
	.byte	102
	.byte	124
	.byte	96
	.byte	-16
	.byte	0
	.byte	0
	.byte	118
	.byte	-52
	.byte	-52
	.byte	124
	.byte	12
	.byte	30
	.byte	0
	.byte	0
	.byte	-36
	.byte	118
	.byte	102
	.byte	96
	.byte	-16
	.byte	0
	.byte	0
	.byte	0
	.byte	124
	.byte	-64
	.byte	120
	.byte	12
	.byte	-8
	.byte	0
	.byte	16
	.byte	48
	.byte	124
	.byte	48
	.byte	48
	.byte	52
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	118
	.byte	0
	.byte	0
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	120
	.byte	48
	.byte	0
	.byte	0
	.byte	0
	.byte	-58
	.byte	-42
	.byte	-2
	.byte	-2
	.byte	108
	.byte	0
	.byte	0
	.byte	0
	.byte	-58
	.byte	108
	.byte	56
	.byte	108
	.byte	-58
	.byte	0
	.byte	0
	.byte	0
	.byte	-52
	.byte	-52
	.byte	-52
	.byte	124
	.byte	12
	.byte	-8
	.byte	0
	.byte	0
	.byte	-4
	.byte	-104
	.byte	48
	.byte	100
	.byte	-4
	.byte	0
	.byte	28
	.byte	48
	.byte	48
	.byte	-32
	.byte	48
	.byte	48
	.byte	28
	.byte	0
	.byte	24
	.byte	24
	.byte	24
	.byte	0
	.byte	24
	.byte	24
	.byte	24
	.byte	0
	.byte	-32
	.byte	48
	.byte	48
	.byte	28
	.byte	48
	.byte	48
	.byte	-32
	.byte	0
	.byte	118
	.byte	-36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.globl	data_h
	.data
	.align	2
	.type	data_h, @object
	.size	data_h, 4
data_h:
	.word	35
	.globl	data_w
	.align	2
	.type	data_w, @object
	.size	data_w, 4
data_w:
	.word	35
	.globl	data_length
	.align	2
	.type	data_length, @object
	.size	data_length, 4
data_length:
	.word	1225
	.globl	data_bits
	.align	2
	.type	data_bits, @object
	.size	data_bits, 4904
data_bits:
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16317688
	.word	16317688
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	16777215
	.word	0
	.text
	.align	2
	.globl	flashscreen
	.ent	flashscreen
flashscreen:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	li	$7,10			# 0xa
	li	$6,1142947840			# 0x44200000
	li	$2,1140850688			# 0x44000000
$L18:
	sw	$4,0($2)
$L16:
	addiu	$2,$2,4
	bnel	$2,$6,$L16
	sw	$4,0($2)

	li	$2,1140850688			# 0x44000000
	li	$3,1142947840			# 0x44200000
	sw	$5,0($2)
$L17:
	addiu	$2,$2,4
	bnel	$2,$3,$L17
	sw	$5,0($2)

	addiu	$7,$7,-1
	bne	$7,$0,$L18
	li	$2,1140850688			# 0x44000000

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	flashscreen
	.size	flashscreen, .-flashscreen
	.align	2
	.globl	memcpy
	.ent	memcpy
memcpy:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	beq	$6,$0,$L25
	addiu	$3,$6,-1

	addu	$2,$5,$3
	addiu	$6,$2,1
$L22:
	lbu	$2,0($5)
	addiu	$5,$5,1
	sb	$2,0($4)
	bne	$5,$6,$L22
	addiu	$4,$4,1

$L25:
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	memcpy
	.size	memcpy, .-memcpy
	.align	2
	.globl	GetVramAddr
	.ent	GetVramAddr
GetVramAddr:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$2,%hi(drawframe)
	lw	$6,%lo(drawframe)($2)
	li	$3,655360			# 0xa0000
	ori	$8,$3,0xa000
	beq	$6,$0,$L31
	move	$7,$4

	lui	$3,%hi(vramtop)
	lw	$4,%lo(vramtop)($3)
	sll	$2,$5,9
	addu	$2,$2,$7
	addu	$4,$8,$4
	sll	$2,$2,2
	addu	$4,$4,$2
	li	$2,1073741824			# 0x40000000
	j	$31
	addu	$2,$4,$2

$L31:
	lui	$3,%hi(vramtop)
	lw	$4,%lo(vramtop)($3)
	sll	$2,$5,9
	move	$8,$0
	addu	$2,$2,$7
	addu	$4,$8,$4
	sll	$2,$2,2
	addu	$4,$4,$2
	li	$2,1073741824			# 0x40000000
	j	$31
	addu	$2,$4,$2

	.set	macro
	.set	reorder
	.end	GetVramAddr
	.size	GetVramAddr, .-GetVramAddr
	.align	2
	.globl	sceKernelLibcGettimeofday
	.ent	sceKernelLibcGettimeofday
sceKernelLibcGettimeofday:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2109
 #NO_APP
	j	$31
	.end	sceKernelLibcGettimeofday
	.size	sceKernelLibcGettimeofday, .-sceKernelLibcGettimeofday
	.align	2
	.globl	rand
	.ent	rand
rand:
	.frame	$sp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	move	$4,$sp
	sw	$31,16($sp)
	jal	sceKernelLibcGettimeofday
	addiu	$5,$sp,8

	lw	$2,4($sp)
	lw	$31,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	rand
	.size	rand, .-rand
	.align	2
	.globl	PutChar
	.ent	PutChar
PutChar:
	.frame	$sp,32,$31		# vars= 0, regs= 7/0, args= 0, gp= 0
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	andi	$8,$8,0x00ff
	lui	$2,%hi(font)
	sw	$21,20($sp)
	sw	$20,16($sp)
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	sll	$8,$8,3
	addiu	$2,$2,%lo(font)
	sw	$31,24($sp)
	move	$20,$7
	seb	$19,$9
	seb	$18,$10
	addu	$17,$8,$2
	move	$21,$6
	jal	GetVramAddr
	seb	$16,$11

	move	$7,$2
	move	$9,$0
	li	$10,8			# 0x8
$L37:
	blezl	$16,$L61
	addiu	$9,$9,1

	move	$4,$7
	move	$8,$0
$L40:
	li	$5,128			# 0x80
	li	$6,8			# 0x8
$L41:
	j	$L42
	move	$3,$0

$L60:
	bnel	$19,$0,$L45
	sw	$21,0($4)

$L45:
	addiu	$2,$3,1
$L62:
	seb	$3,$2
	beq	$16,$3,$L59
	addiu	$4,$4,4

$L42:
	lbu	$2,0($17)
	and	$2,$2,$5
	bne	$2,$0,$L60
	nop

	beq	$18,$0,$L62
	addiu	$2,$3,1

	seb	$3,$2
	sw	$20,0($4)
	bne	$16,$3,$L42
	addiu	$4,$4,4

$L59:
	addiu	$6,$6,-1
	bne	$6,$0,$L41
	srl	$5,$5,1

	addiu	$2,$8,1
	addiu	$7,$7,2048
	seb	$8,$2
	bne	$16,$8,$L40
	move	$4,$7

	addiu	$9,$9,1
$L61:
	bne	$9,$10,$L37
	addiu	$17,$17,1

	lw	$31,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	PutChar
	.size	PutChar, .-PutChar
	.align	2
	.globl	Print
	.ent	Print
Print:
	.frame	$sp,24,$31		# vars= 0, regs= 5/0, args= 0, gp= 0
	.mask	0x800f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	sw	$31,16($sp)
	move	$16,$4
	move	$18,$5
	move	$19,$6
	move	$17,$7
	lb	$2,0($17)
$L80:
	sll	$4,$16,3
	sltu	$12,$16,60
	sll	$5,$18,3
	andi	$8,$2,0x00ff
	move	$6,$19
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	li	$11,1			# 0x1
	addiu	$17,$17,1
	addiu	$16,$16,1
	beq	$2,$0,$L70
	sltu	$3,$18,38

$L77:
	beq	$12,$0,$L78
	lw	$31,16($sp)

	beql	$3,$0,$L79
	lw	$19,12($sp)

	jal	PutChar
	nop

	sltu	$2,$16,60
	bne	$2,$0,$L80
	lb	$2,0($17)

	move	$16,$0
	addiu	$18,$18,1
	sll	$4,$16,3
	sltu	$12,$16,60
	sll	$5,$18,3
	andi	$8,$2,0x00ff
	move	$6,$19
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	li	$11,1			# 0x1
	addiu	$17,$17,1
	addiu	$16,$16,1
	bne	$2,$0,$L77
	sltu	$3,$18,38

$L70:
	lw	$31,16($sp)
$L78:
	lw	$19,12($sp)
$L79:
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	Print
	.size	Print, .-Print
	.align	2
	.globl	PrintFine
	.ent	PrintFine
PrintFine:
	.frame	$sp,24,$31		# vars= 0, regs= 5/0, args= 0, gp= 0
	.mask	0x800f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	sw	$31,16($sp)
	move	$16,$4
	move	$18,$5
	move	$19,$6
	move	$17,$7
	lb	$2,0($17)
$L98:
	move	$4,$16
	sltu	$12,$16,480
	sll	$5,$18,3
	andi	$8,$2,0x00ff
	move	$6,$19
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	li	$11,1			# 0x1
	addiu	$17,$17,1
	addiu	$16,$16,8
	beq	$2,$0,$L88
	sltu	$3,$18,38

$L95:
	beq	$12,$0,$L96
	lw	$31,16($sp)

	beql	$3,$0,$L97
	lw	$19,12($sp)

	jal	PutChar
	nop

	sltu	$2,$16,480
	bne	$2,$0,$L98
	lb	$2,0($17)

	move	$16,$0
	addiu	$18,$18,1
	move	$4,$16
	sltu	$12,$16,480
	sll	$5,$18,3
	andi	$8,$2,0x00ff
	move	$6,$19
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	li	$11,1			# 0x1
	addiu	$17,$17,1
	addiu	$16,$16,8
	bne	$2,$0,$L95
	sltu	$3,$18,38

$L88:
	lw	$31,16($sp)
$L96:
	lw	$19,12($sp)
$L97:
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	PrintFine
	.size	PrintFine, .-PrintFine
	.align	2
	.globl	Fillvram
	.ent	Fillvram
Fillvram:
	.frame	$sp,8,$31		# vars= 0, regs= 2/0, args= 0, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$16,0($sp)
	sw	$31,4($sp)
	move	$16,$4
	move	$5,$0
	jal	GetVramAddr
	move	$4,$0

	move	$3,$2
	li	$2,131072			# 0x20000
	ori	$2,$2,0xa800
$L100:
	addiu	$2,$2,-1
	sw	$16,0($3)
	bne	$2,$0,$L100
	addiu	$3,$3,4

	lw	$31,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	Fillvram
	.size	Fillvram, .-Fillvram
	.align	2
	.globl	sceCtrlReadBufferPositive
	.ent	sceCtrlReadBufferPositive
sceCtrlReadBufferPositive:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x215F;
 #NO_APP
	j	$31
	.end	sceCtrlReadBufferPositive
	.size	sceCtrlReadBufferPositive, .-sceCtrlReadBufferPositive
	.align	2
	.globl	sceCtrlSetSamplingCycle
	.ent	sceCtrlSetSamplingCycle
sceCtrlSetSamplingCycle:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2150;
 #NO_APP
	j	$31
	.end	sceCtrlSetSamplingCycle
	.size	sceCtrlSetSamplingCycle, .-sceCtrlSetSamplingCycle
	.align	2
	.globl	sceCtrlSetSamplingMode
	.ent	sceCtrlSetSamplingMode
sceCtrlSetSamplingMode:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x215D;
 #NO_APP
	j	$31
	.end	sceCtrlSetSamplingMode
	.size	sceCtrlSetSamplingMode, .-sceCtrlSetSamplingMode
	.align	2
	.globl	sceDisplayWaitVblank
	.ent	sceDisplayWaitVblank
sceDisplayWaitVblank:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2154
 #NO_APP
	j	$31
	.end	sceDisplayWaitVblank
	.size	sceDisplayWaitVblank, .-sceDisplayWaitVblank
	.align	2
	.globl	sceDisplayWaitVblankStart
	.ent	sceDisplayWaitVblankStart
sceDisplayWaitVblankStart:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2156
 #NO_APP
	j	$31
	.end	sceDisplayWaitVblankStart
	.size	sceDisplayWaitVblankStart, .-sceDisplayWaitVblankStart
	.align	2
	.globl	WriteNibble
	.ent	WriteNibble
WriteNibble:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	andi	$6,$6,0x00ff
	addiu	$2,$6,55
	addiu	$3,$6,48
	sltu	$6,$6,10
	beq	$6,$0,$L118
	andi	$8,$2,0x00ff

	andi	$8,$3,0x00ff
$L118:
	li	$6,16711680			# 0xff0000
	sll	$4,$4,3
	sll	$5,$5,3
	ori	$6,$6,0xffff
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	j	PutChar
	li	$11,1			# 0x1

	.set	macro
	.set	reorder
	.end	WriteNibble
	.size	WriteNibble, .-WriteNibble
	.align	2
	.globl	WriteByte
	.ent	WriteByte
WriteByte:
	.frame	$sp,16,$31		# vars= 0, regs= 4/0, args= 0, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$16,0($sp)
	andi	$16,$6,0x00ff
	sw	$18,8($sp)
	sw	$17,4($sp)
	move	$18,$5
	move	$17,$4
	sw	$31,12($sp)
	jal	WriteNibble
	srl	$6,$16,4

	addiu	$4,$17,1
	move	$5,$18
	andi	$6,$16,0xf
	lw	$31,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	WriteNibble
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	WriteByte
	.size	WriteByte, .-WriteByte
	.align	2
	.globl	WriteDword
	.ent	WriteDword
WriteDword:
	.frame	$sp,16,$31		# vars= 0, regs= 4/0, args= 0, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$18,8($sp)
	sw	$17,4($sp)
	move	$18,$5
	move	$17,$4
	sw	$16,0($sp)
	move	$16,$6
	sw	$31,12($sp)
	jal	WriteByte
	srl	$6,$6,24

	addiu	$4,$17,2
	move	$5,$18
	jal	WriteByte
	ext	$6,$16,16,8

	addiu	$4,$17,4
	move	$5,$18
	jal	WriteByte
	ext	$6,$16,8,8

	addiu	$4,$17,6
	move	$5,$18
	andi	$6,$16,0x00ff
	lw	$31,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	WriteByte
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	WriteDword
	.size	WriteDword, .-WriteDword
	.align	2
	.globl	WriteNibbleDummy
	.ent	WriteNibbleDummy
WriteNibbleDummy:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	andi	$6,$6,0x00ff
	addiu	$2,$6,55
	addiu	$3,$6,48
	sltu	$6,$6,10
	beq	$6,$0,$L127
	andi	$8,$2,0x00ff

	andi	$8,$3,0x00ff
$L127:
	sll	$4,$4,3
	sll	$5,$5,3
	move	$6,$0
	move	$7,$0
	li	$9,1			# 0x1
	li	$10,1			# 0x1
	j	PutChar
	li	$11,1			# 0x1

	.set	macro
	.set	reorder
	.end	WriteNibbleDummy
	.size	WriteNibbleDummy, .-WriteNibbleDummy
	.align	2
	.globl	WriteByteDummy
	.ent	WriteByteDummy
WriteByteDummy:
	.frame	$sp,16,$31		# vars= 0, regs= 4/0, args= 0, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$16,0($sp)
	andi	$16,$6,0x00ff
	sw	$18,8($sp)
	sw	$17,4($sp)
	move	$18,$5
	move	$17,$4
	sw	$31,12($sp)
	jal	WriteNibbleDummy
	srl	$6,$16,4

	addiu	$4,$17,1
	move	$5,$18
	andi	$6,$16,0xf
	lw	$31,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	WriteNibbleDummy
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	WriteByteDummy
	.size	WriteByteDummy, .-WriteByteDummy
	.align	2
	.globl	WriteDwordDummy
	.ent	WriteDwordDummy
WriteDwordDummy:
	.frame	$sp,16,$31		# vars= 0, regs= 4/0, args= 0, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$18,8($sp)
	sw	$17,4($sp)
	move	$18,$5
	move	$17,$4
	sw	$16,0($sp)
	move	$16,$6
	sw	$31,12($sp)
	jal	WriteByteDummy
	srl	$6,$6,24

	addiu	$4,$17,2
	move	$5,$18
	jal	WriteByteDummy
	ext	$6,$16,16,8

	addiu	$4,$17,4
	move	$5,$18
	jal	WriteByteDummy
	ext	$6,$16,8,8

	addiu	$4,$17,6
	move	$5,$18
	andi	$6,$16,0x00ff
	lw	$31,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	WriteByteDummy
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	WriteDwordDummy
	.size	WriteDwordDummy, .-WriteDwordDummy
	.align	2
	.globl	sceDisplaySetMode
	.ent	sceDisplaySetMode
sceDisplaySetMode:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2146;
 #NO_APP
	j	$31
	.end	sceDisplaySetMode
	.size	sceDisplaySetMode, .-sceDisplaySetMode
	.align	2
	.globl	sceDisplaySetFrameBuf
	.ent	sceDisplaySetFrameBuf
sceDisplaySetFrameBuf:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x214C;
 #NO_APP
	j	$31
	.end	sceDisplaySetFrameBuf
	.size	sceDisplaySetFrameBuf, .-sceDisplaySetFrameBuf
	.align	2
	.globl	FillRect
	.ent	FillRect
FillRect:
	.frame	$sp,32,$31		# vars= 0, regs= 7/0, args= 0, gp= 0
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	sw	$18,8($sp)
	sw	$31,24($sp)
	sw	$21,20($sp)
	sw	$20,16($sp)
	sw	$19,12($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	lw	$16,8($4)
	lw	$21,12($4)
	sltu	$2,$16,$21
	bne	$2,$0,$L147
	move	$18,$5

	lw	$31,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,32

$L147:
	lw	$17,4($4)
	lw	$19,0($4)
	sltu	$20,$19,$17
	move	$4,$19
$L148:
	jal	GetVramAddr
	move	$5,$16

	beq	$20,$0,$L141
	move	$4,$2

	move	$3,$19
$L143:
	addiu	$3,$3,1
	sltu	$2,$3,$17
	sw	$18,0($4)
	bne	$2,$0,$L143
	addiu	$4,$4,4

$L141:
	addiu	$16,$16,1
	sltu	$2,$16,$21
	bnel	$2,$0,$L148
	move	$4,$19

	lw	$31,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	FillRect
	.size	FillRect, .-FillRect
	.align	2
	.globl	MoveToEx
	.ent	MoveToEx
MoveToEx:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$3,%hi(gcursor)
	seh	$4,$4
	seh	$5,$5
	addiu	$2,$3,%lo(gcursor)
	sw	$5,4($2)
	j	$31
	sw	$4,%lo(gcursor)($3)

	.set	macro
	.set	reorder
	.end	MoveToEx
	.size	MoveToEx, .-MoveToEx
	.align	2
	.globl	LineTo
	.ent	LineTo
LineTo:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	LineTo
	.size	LineTo, .-LineTo
	.align	2
	.globl	changeBuffer
	.ent	changeBuffer
changeBuffer:
	.frame	$sp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$31,0($sp)
	jal	sceDisplayWaitVblank
	nop

	move	$5,$0
	jal	GetVramAddr
	move	$4,$0

	move	$4,$2
	li	$5,512			# 0x200
	li	$6,3			# 0x3
	jal	sceDisplaySetFrameBuf
	move	$7,$0

	lui	$3,%hi(drawframe)
	lw	$2,%lo(drawframe)($3)
	lw	$31,0($sp)
	addiu	$sp,$sp,8
	sltu	$2,$2,1
	j	$31
	sw	$2,%lo(drawframe)($3)

	.set	macro
	.set	reorder
	.end	changeBuffer
	.size	changeBuffer, .-changeBuffer
	.align	2
	.globl	DebugValue
	.ent	DebugValue
DebugValue:
	.frame	$sp,16,$31		# vars= 0, regs= 3/0, args= 0, gp= 0
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$17,4($sp)
	sw	$16,0($sp)
	move	$17,$6
	move	$16,$4
	li	$6,16711680			# 0xff0000
	move	$7,$5
	ori	$6,$6,0xffff
	move	$5,$16
	sw	$31,8($sp)
	jal	Print
	move	$4,$0

	move	$5,$16
	move	$6,$17
	lw	$31,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	li	$4,10			# 0xa
	j	WriteDword
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	DebugValue
	.size	DebugValue, .-DebugValue
	.align	2
	.globl	WriteDecimal
	.ent	WriteDecimal
WriteDecimal:
	.frame	$sp,32,$31		# vars= 0, regs= 8/0, args= 0, gp= 0
	.mask	0x807f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	li	$7,1441136640			# 0x55e60000
	ori	$7,$7,0x3b89
	multu	$6,$7
	addiu	$sp,$sp,-32
	li	$2,9961472			# 0x980000
	sw	$19,12($sp)
	ori	$19,$2,0x9680
	li	$2,99942400			# 0x5f50000
	ori	$2,$2,0xe100
	sw	$17,4($sp)
	li	$3,-859045888			# 0xffffffffcccc0000
	sw	$22,24($sp)
	sw	$21,20($sp)
	sw	$20,16($sp)
	sw	$18,8($sp)
	sw	$31,28($sp)
	sw	$16,0($sp)
	move	$18,$4
	move	$21,$5
	mfhi	$7
	srl	$17,$7,25
	ori	$22,$3,0xcccd
	mult	$17,$2
	li	$20,8			# 0x8
	mflo	$2
	subu	$17,$6,$2
$L158:
	bne	$19,$0,1f
	divu	$0,$17,$19
	break	7
1:
	move	$4,$18
	move	$5,$21
	addiu	$20,$20,-1
	addiu	$18,$18,1
	mflo	$16
	andi	$16,$16,0x00ff
	jal	WriteNibble
	move	$6,$16

	multu	$19,$22
	mfhi	$2
	mtlo	$17
	msub	$16,$19
	srl	$19,$2,3
	bne	$20,$0,$L158
	mflo	$17

	lw	$31,28($sp)
	lw	$22,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	WriteDecimal
	.size	WriteDecimal, .-WriteDecimal
	.align	2
	.globl	initScreenAndCtrl
	.ent	initScreenAndCtrl
initScreenAndCtrl:
	.frame	$sp,8,$31		# vars= 0, regs= 2/0, args= 0, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$16,0($sp)
	move	$4,$0
	lui	$16,%hi(drawframe)
	li	$5,512			# 0x200
	li	$6,272			# 0x110
	sw	$31,4($sp)
	jal	sceDisplaySetMode
	sw	$0,%lo(drawframe)($16)

	lui	$3,%hi(vramtop)
	lw	$4,%lo(vramtop)($3)
	li	$5,512			# 0x200
	li	$6,3			# 0x3
	jal	sceDisplaySetFrameBuf
	li	$7,1			# 0x1

	jal	Fillvram
	move	$4,$0

	li	$2,1			# 0x1
	move	$4,$0
	jal	Fillvram
	sw	$2,%lo(drawframe)($16)

	jal	sceCtrlSetSamplingCycle
	move	$4,$0

	lw	$31,4($sp)
	lw	$16,0($sp)
	li	$4,1			# 0x1
	j	sceCtrlSetSamplingMode
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	initScreenAndCtrl
	.size	initScreenAndCtrl, .-initScreenAndCtrl
	.align	2
	.globl	strlen
	.ent	strlen
strlen:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lb	$2,0($4)
	bne	$2,$0,$L169
	move	$2,$0

	j	$31
	nop

$L169:
	j	$L169
	nop

	.set	macro
	.set	reorder
	.end	strlen
	.size	strlen, .-strlen
	.align	2
	.globl	sceIoOpen
	.ent	sceIoOpen
sceIoOpen:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x208F;
 #NO_APP
	j	$31
	.end	sceIoOpen
	.size	sceIoOpen, .-sceIoOpen
	.align	2
	.globl	sceIoClose
	.ent	sceIoClose
sceIoClose:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x208D;
 #NO_APP
	j	$31
	.end	sceIoClose
	.size	sceIoClose, .-sceIoClose
	.align	2
	.globl	sceIoRead
	.ent	sceIoRead
sceIoRead:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2091;
 #NO_APP
	j	$31
	.end	sceIoRead
	.size	sceIoRead, .-sceIoRead
	.align	2
	.globl	sceIoWrite
	.ent	sceIoWrite
sceIoWrite:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2093;
 #NO_APP
	j	$31
	.end	sceIoWrite
	.size	sceIoWrite, .-sceIoWrite
	.align	2
	.globl	sceKernelExitGame
	.ent	sceKernelExitGame
sceKernelExitGame:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20F2
 #NO_APP
	j	$31
	.end	sceKernelExitGame
	.size	sceKernelExitGame, .-sceKernelExitGame
	.align	2
	.globl	sceKernelTerminateDeleteThread
	.ent	sceKernelTerminateDeleteThread
sceKernelTerminateDeleteThread:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2074;
 #NO_APP
	j	$31
	.end	sceKernelTerminateDeleteThread
	.size	sceKernelTerminateDeleteThread, .-sceKernelTerminateDeleteThread
	.align	2
	.globl	sceKernelDeleteCallback
	.ent	sceKernelDeleteCallback
sceKernelDeleteCallback:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x200E;
 #NO_APP
	j	$31
	.end	sceKernelDeleteCallback
	.size	sceKernelDeleteCallback, .-sceKernelDeleteCallback
	.align	2
	.globl	sceKernelDelayThread
	.ent	sceKernelDelayThread
sceKernelDelayThread:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x201c;
 #NO_APP
	j	$31
	.end	sceKernelDelayThread
	.size	sceKernelDelayThread, .-sceKernelDelayThread
	.align	2
	.globl	sceKernelGetThreadId
	.ent	sceKernelGetThreadId
sceKernelGetThreadId:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x207B
 #NO_APP
	j	$31
	.end	sceKernelGetThreadId
	.size	sceKernelGetThreadId, .-sceKernelGetThreadId
	.align	2
	.globl	sceKernelAllocPartitionMemory
	.ent	sceKernelAllocPartitionMemory
sceKernelAllocPartitionMemory:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2169;
 #NO_APP
	j	$31
	.end	sceKernelAllocPartitionMemory
	.size	sceKernelAllocPartitionMemory, .-sceKernelAllocPartitionMemory
	.align	2
	.globl	sceKernelFreePartitionMemory
	.ent	sceKernelFreePartitionMemory
sceKernelFreePartitionMemory:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20E2;
 #NO_APP
	j	$31
	.end	sceKernelFreePartitionMemory
	.size	sceKernelFreePartitionMemory, .-sceKernelFreePartitionMemory
	.align	2
	.globl	sceKernelGetBlockHeadAddr
	.ent	sceKernelGetBlockHeadAddr
sceKernelGetBlockHeadAddr:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20e3;
 #NO_APP
	j	$31
	.end	sceKernelGetBlockHeadAddr
	.size	sceKernelGetBlockHeadAddr, .-sceKernelGetBlockHeadAddr
	.align	2
	.globl	sceKernelCreateThread
	.ent	sceKernelCreateThread
sceKernelCreateThread:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x206d
 #NO_APP
	j	$31
	.end	sceKernelCreateThread
	.size	sceKernelCreateThread, .-sceKernelCreateThread
	.align	2
	.globl	sceKernelStartThread
	.ent	sceKernelStartThread
sceKernelStartThread:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x206f
 #NO_APP
	j	$31
	.end	sceKernelStartThread
	.size	sceKernelStartThread, .-sceKernelStartThread
	.align	2
	.globl	sceKernelMaxFreeMemSize
	.ent	sceKernelMaxFreeMemSize
sceKernelMaxFreeMemSize:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20DF;
 #NO_APP
	j	$31
	.end	sceKernelMaxFreeMemSize
	.size	sceKernelMaxFreeMemSize, .-sceKernelMaxFreeMemSize
	.align	2
	.globl	sceKernelDcacheWritebackInvalidateAll
	.ent	sceKernelDcacheWritebackInvalidateAll
sceKernelDcacheWritebackInvalidateAll:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20c7
 #NO_APP
	j	$31
	.end	sceKernelDcacheWritebackInvalidateAll
	.size	sceKernelDcacheWritebackInvalidateAll, .-sceKernelDcacheWritebackInvalidateAll
	.align	2
	.globl	sceKernelDeleteFpl
	.ent	sceKernelDeleteFpl
sceKernelDeleteFpl:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x204C
 #NO_APP
	j	$31
	.end	sceKernelDeleteFpl
	.size	sceKernelDeleteFpl, .-sceKernelDeleteFpl
	.align	2
	.globl	sceKernelDeleteSema
	.ent	sceKernelDeleteSema
sceKernelDeleteSema:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2021
 #NO_APP
	j	$31
	.end	sceKernelDeleteSema
	.size	sceKernelDeleteSema, .-sceKernelDeleteSema
	.align	2
	.globl	sceKernelReleaseSubIntrHandler
	.ent	sceKernelReleaseSubIntrHandler
sceKernelReleaseSubIntrHandler:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2001
 #NO_APP
	j	$31
	.end	sceKernelReleaseSubIntrHandler
	.size	sceKernelReleaseSubIntrHandler, .-sceKernelReleaseSubIntrHandler
	.align	2
	.globl	sceKernelStopModule
	.ent	sceKernelStopModule
sceKernelStopModule:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20D7
 #NO_APP
	j	$31
	.end	sceKernelStopModule
	.size	sceKernelStopModule, .-sceKernelStopModule
	.align	2
	.globl	sceKernelUnloadModule
	.ent	sceKernelUnloadModule
sceKernelUnloadModule:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20D8
 #NO_APP
	j	$31
	.end	sceKernelUnloadModule
	.size	sceKernelUnloadModule, .-sceKernelUnloadModule
	.align	2
	.globl	sceKernelSelfStopUnloadModule
	.ent	sceKernelSelfStopUnloadModule
sceKernelSelfStopUnloadModule:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20D9
 #NO_APP
	j	$31
	.end	sceKernelSelfStopUnloadModule
	.size	sceKernelSelfStopUnloadModule, .-sceKernelSelfStopUnloadModule
	.align	2
	.globl	sceKernelVolatileMemUnlock
	.ent	sceKernelVolatileMemUnlock
sceKernelVolatileMemUnlock:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x20EF
 #NO_APP
	j	$31
	.end	sceKernelVolatileMemUnlock
	.size	sceKernelVolatileMemUnlock, .-sceKernelVolatileMemUnlock
	.align	2
	.globl	sceUmdUnRegisterUMDCallBack
	.ent	sceUmdUnRegisterUMDCallBack
sceUmdUnRegisterUMDCallBack:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x21BF
 #NO_APP
	j	$31
	.end	sceUmdUnRegisterUMDCallBack
	.size	sceUmdUnRegisterUMDCallBack, .-sceUmdUnRegisterUMDCallBack
	.align	2
	.globl	scePowerUnregisterCallback
	.ent	scePowerUnregisterCallback
scePowerUnregisterCallback:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x219B
 #NO_APP
	j	$31
	.end	scePowerUnregisterCallback
	.size	scePowerUnregisterCallback, .-scePowerUnregisterCallback
	.align	2
	.globl	sceGeUnsetCallback
	.ent	sceGeUnsetCallback
sceGeUnsetCallback:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2107
 #NO_APP
	j	$31
	.end	sceGeUnsetCallback
	.size	sceGeUnsetCallback, .-sceGeUnsetCallback
	.align	2
	.globl	sceUtilitySavedataShutdownStart
	.ent	sceUtilitySavedataShutdownStart
sceUtilitySavedataShutdownStart:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2201
 #NO_APP
	j	$31
	.end	sceUtilitySavedataShutdownStart
	.size	sceUtilitySavedataShutdownStart, .-sceUtilitySavedataShutdownStart
	.align	2
	.globl	sceUtilitySavedataGetStatus
	.ent	sceUtilitySavedataGetStatus
sceUtilitySavedataGetStatus:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2203
 #NO_APP
	j	$31
	.end	sceUtilitySavedataGetStatus
	.size	sceUtilitySavedataGetStatus, .-sceUtilitySavedataGetStatus
	.align	2
	.globl	sceUtilitySavedataUpdate
	.ent	sceUtilitySavedataUpdate
sceUtilitySavedataUpdate:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2202
 #NO_APP
	j	$31
	.end	sceUtilitySavedataUpdate
	.size	sceUtilitySavedataUpdate, .-sceUtilitySavedataUpdate
	.align	2
	.globl	sceAudioChRelease
	.ent	sceAudioChRelease
sceAudioChRelease:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
 #APP
	syscall 0x2135
 #NO_APP
	j	$31
	.end	sceAudioChRelease
	.size	sceAudioChRelease, .-sceAudioChRelease
	.align	2
	.globl	find_gta_sceResident
	.ent	find_gta_sceResident
find_gta_sceResident:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	move	$9,$5
	beq	$5,$0,$L233
	move	$10,$4

	lui	$2,%hi(hash_values)
	addiu	$11,$2,%lo(hash_values)
	move	$8,$0
	move	$6,$0
	move	$7,$0
	j	$L235
	li	$12,20			# 0x14

$L244:
	move	$8,$0
	move	$7,$0
	addiu	$6,$6,1
$L246:
	beql	$9,$6,$L245
	move	$8,$0

$L235:
	addu	$3,$7,$11
	addu	$2,$6,$10
	lbu	$5,0($2)
	lbu	$4,0($3)
	addiu	$7,$7,1
	bne	$5,$4,$L244
	movz	$8,$6,$8

	bne	$7,$12,$L246
	addiu	$6,$6,1

	j	$31
	move	$2,$8

$L233:
	move	$8,$0
$L245:
	j	$31
	move	$2,$8

	.set	macro
	.set	reorder
	.end	find_gta_sceResident
	.size	find_gta_sceResident, .-find_gta_sceResident
	.align	2
	.globl	findKnownSyscall
	.ent	findKnownSyscall
findKnownSyscall:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$3,%hi(functions)
	lw	$2,%lo(functions)($3)
	beq	$2,$0,$L249
	nop

	beq	$2,$4,$L258
	move	$6,$0

	lui	$2,%hi(functions+16)
	addiu	$2,$2,%lo(functions+16)
	lw	$5,0($2)
$L259:
	addiu	$6,$6,1
	beq	$5,$0,$L249
	addiu	$2,$2,16

	bnel	$5,$4,$L259
	lw	$5,0($2)

	addiu	$3,$3,%lo(functions)
	sll	$2,$6,4
	addu	$2,$2,$3
	j	$31
	lw	$2,12($2)

$L249:
	j	$31
	move	$2,$0

$L258:
	addiu	$3,$3,%lo(functions)
	sll	$2,$6,4
	addu	$2,$2,$3
	j	$31
	lw	$2,12($2)

	.set	macro
	.set	reorder
	.end	findKnownSyscall
	.size	findKnownSyscall, .-findKnownSyscall
	.align	2
	.globl	findNIDs
	.ent	findNIDs
findNIDs:
	.frame	$sp,40,$31		# vars= 0, regs= 10/0, args= 0, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-40
	sw	$23,28($sp)
	sw	$22,24($sp)
	sw	$21,20($sp)
	sw	$31,36($sp)
	sw	$fp,32($sp)
	sw	$20,16($sp)
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	lui	$2,%hi(functions)
	lw	$3,%lo(functions)($2)
	move	$21,$4
	move	$23,$6
	beq	$3,$0,$L261
	move	$22,$7

	lui	$2,%hi(functions+16)
	addiu	$20,$2,%lo(functions+16)
	j	$L263
	sltu	$fp,$6,$7

$L278:
$L295:
	beq	$2,$0,$L261
	addiu	$20,$20,16

$L263:
	beql	$fp,$0,$L295
	lw	$2,0($20)

	lw	$19,-8($20)
	addu	$16,$21,$23
	j	$L264
	move	$17,$23

$L265:
	addiu	$17,$17,20
	sltu	$2,$17,$22
	beql	$2,$0,$L295
	lw	$2,0($20)

$L264:
	lw	$4,0($16)
	li	$18,-142606336			# 0xfffffffff7800000
	move	$5,$19
	addu	$4,$4,$18
	jal	strcmp
	addu	$4,$21,$4

	bne	$2,$0,$L265
	addiu	$16,$16,20

	addu	$2,$21,$17
	lw	$3,16($2)
	lw	$4,12($2)
	lhu	$11,10($2)
	addu	$2,$3,$18
	beq	$11,$0,$L267
	addu	$3,$4,$18

	addu	$6,$21,$2
	li	$2,-16777216			# 0xffffffffff000000
	addu	$4,$21,$3
	ori	$14,$2,0xf
	move	$9,$0
	move	$12,$0
	j	$L269
	li	$13,1073741824			# 0x40000000

$L270:
	addiu	$9,$9,1
$L296:
	sltu	$2,$9,$11
	addiu	$4,$4,4
	beq	$2,$0,$L291
	addiu	$6,$6,8

$L269:
	lw	$3,0($4)
	lw	$2,-16($20)
	bnel	$3,$2,$L296
	addiu	$9,$9,1

	lw	$10,4($6)
	lw	$3,-12($20)
	srl	$2,$10,6
	bne	$3,$0,$L272
	sw	$2,-4($20)

	addiu	$9,$9,1
	sltu	$2,$9,$11
	li	$12,1			# 0x1
	addiu	$4,$4,4
	bne	$2,$0,$L269
	addiu	$6,$6,8

$L291:
	bnel	$12,$0,$L278
	lw	$2,0($20)

$L267:
	lui	$5,%hi(numfailed)
	lw	$4,%lo(numfailed)($5)
	lw	$6,-16($20)
	lui	$2,%hi(failednids)
	sll	$3,$4,2
	addiu	$2,$2,%lo(failednids)
	addu	$3,$3,$2
	sw	$6,0($3)
	lw	$2,0($20)
	addiu	$4,$4,1
	sw	$4,%lo(numfailed)($5)
	bne	$2,$0,$L263
	addiu	$20,$20,16

$L261:
	li	$4,691732480			# 0x293b0000
	jal	findKnownSyscall
	ori	$4,$4,0x45b8

	li	$3,8315			# 0x207b
	beq	$2,$3,$L292
	li	$4,-74579968			# 0xfffffffffb8e0000

	jal	findKnownSyscall
	ori	$4,$4,0x22ec

	li	$4,-905707520			# 0xffffffffca040000
	move	$16,$2
	jal	findKnownSyscall
	ori	$4,$4,0xa2b9

	addiu	$16,$16,-2
	beq	$2,$16,$L293
	li	$3,260			# 0x104

	lui	$2,%hi(gDetectedFirmware)
	sw	$3,%lo(gDetectedFirmware)($2)
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$23,28($sp)
	lw	$22,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,40

$L292:
	li	$3,200			# 0xc8
	lui	$2,%hi(gDetectedFirmware)
	sw	$3,%lo(gDetectedFirmware)($2)
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$23,28($sp)
	lw	$22,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,40

$L272:
	or	$2,$3,$13
	move	$3,$2
	move	$8,$14
	li	$7,12			# 0xc
	addiu	$5,$2,80
	j	$L274
	sw	$2,-12($20)

$L294:
	beql	$5,$3,$L296
	addiu	$9,$9,1

$L274:
	lw	$2,0($3)
	and	$2,$2,$8
	bnel	$2,$7,$L294
	addiu	$3,$3,4

	li	$12,1			# 0x1
	j	$L270
	sw	$10,0($3)

$L293:
	li	$3,250			# 0xfa
	lui	$2,%hi(gDetectedFirmware)
	sw	$3,%lo(gDetectedFirmware)($2)
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$23,28($sp)
	lw	$22,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	findNIDs
	.size	findNIDs, .-findNIDs
	.align	2
	.globl	initial_setup
	.ent	initial_setup
initial_setup:
	.frame	$sp,16,$31		# vars= 0, regs= 3/0, args= 0, gp= 0
	.mask	0x80030000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-16
	sw	$17,4($sp)
	sw	$16,0($sp)
	move	$17,$4
	sw	$31,8($sp)
	jal	find_gta_sceResident
	move	$16,$5

	addu	$3,$17,$2
	li	$8,-142606336			# 0xfffffffff7800000
	move	$4,$17
	bne	$2,$0,$L301
	move	$5,$16

	lw	$31,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,16

$L301:
	lw	$2,28($3)
	lw	$31,8($sp)
	lw	$16,0($sp)
	addu	$2,$2,$8
	addu	$2,$17,$2
	lw	$7,48($2)
	lw	$6,44($2)
	lw	$17,4($sp)
	addu	$7,$7,$8
	addu	$6,$6,$8
	j	findNIDs
	addiu	$sp,$sp,16

	.set	macro
	.set	reorder
	.end	initial_setup
	.size	initial_setup, .-initial_setup
	.align	2
	.globl	GetFX
	.ent	GetFX
GetFX:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	mtc1	$5,$f1
	mtc1	$4,$f2
	cvt.s.w	$f0,$f1
	cvt.s.w	$f1,$f2
	mul.s	$f0,$f0,$f1
	mtc1	$6,$f1
	nop
	cvt.s.w	$f2,$f1
	div.s	$f0,$f0,$f2
	trunc.w.s $f0,$f0
	mfc1	$2,$f0
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	GetFX
	.size	GetFX, .-GetFX
	.align	2
	.globl	GetFZ
	.ent	GetFZ
GetFZ:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	mtc1	$5,$f1
	mtc1	$4,$f2
	cvt.s.w	$f0,$f1
	cvt.s.w	$f1,$f2
	mul.s	$f0,$f0,$f1
	mtc1	$6,$f1
	nop
	cvt.s.w	$f2,$f1
	div.s	$f0,$f0,$f2
	trunc.w.s $f0,$f0
	mfc1	$2,$f0
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	GetFZ
	.size	GetFZ, .-GetFZ
	.align	2
	.globl	fill_rect
	.ent	fill_rect
fill_rect:
	.frame	$sp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$4,0($sp)
	sw	$5,8($sp)
	move	$4,$sp
	move	$5,$8
	sw	$31,16($sp)
	sw	$6,4($sp)
	jal	FillRect
	sw	$7,12($sp)

	lw	$31,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fill_rect
	.size	fill_rect, .-fill_rect
	.align	2
	.globl	init_app
	.ent	init_app
init_app:
	.frame	$sp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$31,0($sp)
	jal	initScreenAndCtrl
	nop

	move	$4,$0
	move	$5,$0
	li	$6,480			# 0x1e0
	li	$7,272			# 0x110
	jal	fill_rect
	move	$8,$0

	lw	$31,0($sp)
	j	changeBuffer
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	init_app
	.size	init_app, .-init_app
	.align	2
	.globl	swap_buffer
	.ent	swap_buffer
swap_buffer:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	changeBuffer
	nop

	.set	macro
	.set	reorder
	.end	swap_buffer
	.size	swap_buffer, .-swap_buffer
	.align	2
	.globl	loop
	.ent	loop
loop:
	.frame	$sp,32,$31		# vars= 0, regs= 7/0, args= 0, gp= 0
	.mask	0x803f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-32
	li	$2,715784192			# 0x2aaa0000
	li	$6,480			# 0x1e0
	li	$7,272			# 0x110
	move	$8,$0
	sw	$21,20($sp)
	sw	$19,12($sp)
	sw	$17,4($sp)
	ori	$19,$2,0xaaab
	sw	$16,0($sp)
	move	$17,$4
	move	$16,$0
	move	$4,$0
	move	$21,$5
	move	$5,$0
	sw	$31,24($sp)
	sw	$20,16($sp)
	jal	fill_rect
	sw	$18,8($sp)

	jal	$17
	lui	$20,%hi(gpaddata)

	jal	swap_buffer
	addiu	$18,$20,%lo(gpaddata)

	mult	$16,$19
	sra	$6,$16,31
	addiu	$4,$20,%lo(gpaddata)
	mfhi	$2
	subu	$2,$2,$6
	sll	$3,$2,3
	sll	$2,$2,1
	subu	$3,$3,$2
	beq	$16,$3,$L320
	li	$5,1			# 0x1

$L314:
	addiu	$16,$16,1
	li	$6,480			# 0x1e0
$L323:
	move	$4,$0
	move	$5,$0
	li	$7,272			# 0x110
	jal	fill_rect
	move	$8,$0

	jal	$17
	nop

	jal	swap_buffer
	nop

	mult	$16,$19
	sra	$6,$16,31
	addiu	$4,$20,%lo(gpaddata)
	mfhi	$2
	subu	$2,$2,$6
	sll	$3,$2,3
	sll	$2,$2,1
	subu	$3,$3,$2
	bne	$16,$3,$L314
	li	$5,1			# 0x1

$L320:
	jal	sceCtrlReadBufferPositive
	nop

	lw	$6,4($18)
	move	$4,$0
	jal	WriteDwordDummy
	li	$5,22			# 0x16

	lw	$3,4($18)
	andi	$2,$3,0x4000
	bne	$2,$0,$L321
	move	$4,$0

$L316:
	andi	$2,$3,0x2000
	beq	$2,$0,$L314
	li	$4,1			# 0x1

	jal	$21
	addiu	$16,$16,1

	j	$L323
	li	$6,480			# 0x1e0

$L321:
	jal	$21
	nop

	j	$L316
	lw	$3,4($18)

	.set	macro
	.set	reorder
	.end	loop
	.size	loop, .-loop
	.align	2
	.globl	set_pixel
	.ent	set_pixel
set_pixel:
	.frame	$sp,8,$31		# vars= 0, regs= 2/0, args= 0, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$31,4($sp)
	sw	$16,0($sp)
	jal	GetVramAddr
	move	$16,$6

	sw	$16,0($2)
	lw	$31,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	set_pixel
	.size	set_pixel, .-set_pixel
	.align	2
	.globl	clean_app
	.ent	clean_app
clean_app:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	clean_app
	.size	clean_app, .-clean_app
	.align	2
	.globl	draw_text
	.ent	draw_text
draw_text:
	.frame	$sp,72,$31		# vars= 32, regs= 10/0, args= 0, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	mult	$5,$6
	addiu	$sp,$sp,-72
	sw	$10,28($sp)
	sw	$4,16($sp)
	lw	$4,28($sp)
	sw	$fp,64($sp)
	sw	$23,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$31,68($sp)
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	sw	$7,20($sp)
	sw	$9,24($sp)
	mflo	$2
	sw	$2,12($sp)
	sw	$8,4($sp)
	sw	$7,8($sp)
	sw	$0,0($sp)
	move	$fp,$5
	jal	strlen
	move	$21,$6

	lw	$3,0($sp)
	move	$23,$0
	slt	$2,$3,$2
	beq	$2,$0,$L352
	move	$22,$0

	lw	$3,28($sp)
$L365:
	lw	$4,0($sp)
	addu	$2,$3,$4
	lb	$2,0($2)
	li	$3,10			# 0xa
	beq	$2,$3,$L356
	lw	$3,12($sp)

	lw	$4,16($sp)
	mult	$2,$3
	mflo	$2
	sll	$2,$2,2
	blez	$fp,$L334
	addu	$18,$4,$2

	lw	$19,8($sp)
	move	$20,$0
$L336:
	blezl	$21,$L362
	addiu	$20,$20,1

	lw	$17,4($sp)
	j	$L337
	move	$16,$0

$L358:
	addiu	$16,$16,1
$L363:
	addiu	$18,$18,4
	beq	$21,$16,$L347
	addiu	$17,$17,1

$L337:
	lw	$2,0($18)
	beql	$2,$0,$L363
	addiu	$16,$16,1

	blez	$17,$L340
	move	$23,$20

	blez	$19,$L340
	slt	$2,$17,272

	beq	$2,$0,$L340
	slt	$3,$19,480

	move	$5,$17
	move	$4,$19
	bne	$3,$0,$L357
	lw	$6,24($sp)

$L340:
	slt	$2,$22,$16
$L361:
	bnel	$2,$0,$L358
	move	$22,$16

	addiu	$16,$16,1
	move	$23,$20
	addiu	$18,$18,4
	bne	$21,$16,$L337
	addiu	$17,$17,1

$L347:
	addiu	$20,$20,1
$L362:
	bne	$fp,$20,$L336
	addiu	$19,$19,1

$L334:
	lw	$2,8($sp)
	addu	$2,$2,$23
	sw	$2,8($sp)
	addu	$2,$23,$2
	slt	$2,$2,480
	bne	$2,$0,$L364
	lw	$3,4($sp)

	lw	$4,20($sp)
	addu	$3,$3,$22
	sw	$3,4($sp)
	sw	$4,8($sp)
	lw	$3,4($sp)
$L364:
	addu	$2,$3,$22
	slt	$2,$2,273
	beq	$2,$0,$L359
	lw	$4,0($sp)

	addiu	$4,$4,1
	sw	$4,0($sp)
$L360:
	jal	strlen
	lw	$4,28($sp)

	lw	$3,0($sp)
	slt	$2,$3,$2
	bne	$2,$0,$L365
	lw	$3,28($sp)

$L352:
	lw	$31,68($sp)
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,72

$L357:
	jal	set_pixel
	nop

	j	$L361
	slt	$2,$22,$16

$L356:
	lw	$4,4($sp)
	lw	$2,20($sp)
	addu	$4,$4,$22
	sw	$4,4($sp)
	lw	$4,0($sp)
	sw	$2,8($sp)
	addiu	$4,$4,1
	j	$L360
	sw	$4,0($sp)

$L359:
	lw	$31,68($sp)
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	li	$2,1			# 0x1
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
	.end	draw_text
	.size	draw_text, .-draw_text
	.align	2
	.globl	draw_bitmap
	.ent	draw_bitmap
draw_bitmap:
	.frame	$sp,56,$31		# vars= 16, regs= 10/0, args= 0, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-56
	sw	$fp,48($sp)
	sw	$23,44($sp)
	sw	$22,40($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$31,52($sp)
	sw	$21,36($sp)
	sw	$20,32($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	move	$19,$7
	sw	$4,0($sp)
	move	$fp,$5
	sw	$6,4($sp)
	move	$18,$8
	sw	$9,8($sp)
	move	$23,$10
	blez	$7,$L375
	move	$22,$11

	move	$20,$0
$L369:
	blez	$18,$L373
	lw	$4,8($sp)

	move	$5,$20
	jal	GetFX
	move	$6,$19

	move	$21,$2
	lw	$2,4($sp)
	move	$16,$0
	addu	$17,$18,$2
	subu	$5,$18,$16
$L377:
	move	$4,$23
	jal	GetFZ
	move	$6,$18

	mult	$19,$2
	lw	$3,0($sp)
	move	$5,$17
	addiu	$16,$16,1
	addiu	$17,$17,-1
	addu	$4,$20,$fp
	mflo	$2
	addu	$2,$21,$2
	sll	$2,$2,2
	addu	$2,$2,$3
	lw	$3,0($2)
	beq	$3,$22,$L371
	move	$6,$3

	jal	set_pixel
	nop

$L371:
	bne	$18,$16,$L377
	subu	$5,$18,$16

$L373:
	addiu	$20,$20,1
	bne	$19,$20,$L369
	nop

$L375:
	lw	$31,52($sp)
	lw	$fp,48($sp)
	lw	$23,44($sp)
	lw	$22,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
	.end	draw_bitmap
	.size	draw_bitmap, .-draw_bitmap
	.align	2
	.globl	map_rgb
	.ent	map_rgb
map_rgb:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	$31
	li	$2,255			# 0xff

	.set	macro
	.set	reorder
	.end	map_rgb
	.size	map_rgb, .-map_rgb
	.align	2
	.globl	nextmove
	.ent	nextmove
nextmove:
	.frame	$sp,8,$31		# vars= 0, regs= 2/0, args= 0, gp= 0
	.mask	0x00030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	lui	$15,%hi(pos)
	sw	$17,4($sp)
	sw	$16,0($sp)
	addiu	$2,$15,%lo(pos)
	lw	$10,%lo(pos)($15)
	lw	$12,4($2)
	lui	$25,%hi(i)
	lui	$16,%hi(horizontal)
	lui	$17,%hi(vertical)
	lui	$2,%hi(board)
	lui	$3,%hi(htable)
	sw	$0,%lo(i)($25)
	addiu	$14,$2,%lo(board)
	addiu	$24,$3,%lo(htable)
	li	$4,100			# 0x64
	move	$9,$0
	li	$13,-1			# 0xffffffffffffffff
	addiu	$8,$16,%lo(horizontal)
	addiu	$7,$17,%lo(vertical)
	li	$11,8			# 0x8
	lw	$2,0($8)
$L398:
	lw	$3,0($7)
	addiu	$8,$8,4
	addu	$5,$10,$2
	sltu	$2,$5,8
	addiu	$7,$7,4
	beq	$2,$0,$L382
	addu	$3,$12,$3

	bltz	$3,$L382
	slt	$6,$3,8

	sll	$2,$5,3
	addu	$2,$2,$3
	sll	$2,$2,2
	beq	$6,$0,$L382
	addu	$3,$2,$14

	addu	$5,$2,$24
	lw	$2,0($3)
	bnel	$2,$0,$L397
	addiu	$9,$9,1

	lw	$3,0($5)
	slt	$2,$3,$4
	beql	$2,$0,$L397
	addiu	$9,$9,1

	beql	$3,$0,$L397
	addiu	$9,$9,1

	move	$4,$3
	move	$13,$9
$L382:
	addiu	$9,$9,1
$L397:
	bnel	$9,$11,$L398
	lw	$2,0($8)

	li	$2,8			# 0x8
	li	$3,-1			# 0xffffffffffffffff
	beq	$13,$3,$L393
	sw	$2,%lo(i)($25)

	sll	$2,$13,2
	addiu	$4,$16,%lo(horizontal)
	addiu	$3,$17,%lo(vertical)
	addu	$3,$2,$3
	addiu	$8,$15,%lo(pos)
	addu	$2,$2,$4
	lw	$5,4($8)
	lui	$9,%hi(moves)
	lw	$6,0($2)
	lw	$7,0($3)
	sll	$2,$10,3
	lw	$4,%lo(moves)($9)
	lui	$3,%hi(board)
	addu	$2,$2,$12
	addiu	$11,$3,%lo(board)
	sll	$2,$2,2
	addu	$3,$5,$7
	addu	$2,$2,$11
	li	$5,1			# 0x1
	addu	$6,$6,$10
	addiu	$4,$4,1
	sw	$5,0($2)
	li	$2,63			# 0x3f
	sw	$3,4($8)
	sw	$6,%lo(pos)($15)
	beq	$4,$2,$L396
	sw	$4,%lo(moves)($9)

$L393:
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,8

$L396:
	sll	$2,$6,3
	addu	$2,$2,$3
	sll	$2,$2,2
	addu	$2,$2,$11
	li	$3,64			# 0x40
	sw	$3,%lo(moves)($9)
	sw	$5,0($2)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	nextmove
	.size	nextmove, .-nextmove
	.align	2
	.globl	clearboard
	.ent	clearboard
clearboard:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$8,%hi(i)
	lui	$2,%hi(board)
	sw	$0,%lo(i)($8)
	addiu	$7,$2,%lo(board)
	move	$5,$0
	li	$4,8			# 0x8
	li	$6,8			# 0x8
	sll	$2,$5,5
$L409:
	addu	$2,$2,$7
	move	$3,$0
$L401:
	addiu	$3,$3,1
	sw	$0,0($2)
	bne	$3,$4,$L401
	addiu	$2,$2,4

	addiu	$5,$5,1
	bne	$5,$6,$L409
	sll	$2,$5,5

	lui	$2,%hi(z)
	sw	$5,%lo(i)($8)
	j	$31
	sw	$5,%lo(z)($2)

	.set	macro
	.set	reorder
	.end	clearboard
	.size	clearboard, .-clearboard
	.align	2
	.globl	init
	.ent	init
init:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	lui	$5,%hi(pos)
	addiu	$4,$5,%lo(pos)
	li	$2,6			# 0x6
	li	$3,1			# 0x1
	sw	$2,4($4)
	j	clearboard
	sw	$3,%lo(pos)($5)

	.set	macro
	.set	reorder
	.end	init
	.size	init, .-init
	.align	2
	.globl	Main
	.ent	Main
Main:
	.frame	$sp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$31,0($sp)
	jal	init_app
	nop

	jal	init
	nop

	lui	$4,%hi(render)
	lui	$5,%hi(joy_button)
	lw	$31,0($sp)
	addiu	$4,$4,%lo(render)
	addiu	$5,$5,%lo(joy_button)
	j	loop
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	Main
	.size	Main, .-Main
	.section	.text.start,"ax",@progbits
	.align	2
	.globl	_start
	.ent	_start
_start:
	.frame	$sp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	li	$4,142606336			# 0x8800000
	sw	$31,0($sp)
	jal	initial_setup
	li	$5,25165824			# 0x1800000

	jal	Main
	nop

$L415:
	j	$L415
	nop

	.set	macro
	.set	reorder
	.end	_start
	.size	_start, .-_start
	.text
	.align	2
	.globl	joy_button
	.ent	joy_button
joy_button:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	beq	$4,$0,$L419
	li	$2,1			# 0x1

	beq	$4,$2,$L423
	nop

	j	$31
	nop

$L419:
	j	nextmove
	nop

$L423:
	j	init
	nop

	.set	macro
	.set	reorder
	.end	joy_button
	.size	joy_button, .-joy_button
	.align	2
	.globl	drawboard
	.ent	drawboard
drawboard:
	.frame	$sp,40,$31		# vars= 0, regs= 10/0, args= 0, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-40
	li	$2,100			# 0x64
	lui	$3,%hi(startx)
	sw	$fp,32($sp)
	sw	$20,16($sp)
	sw	$2,%lo(startx)($3)
	lui	$20,%hi(counter)
	lui	$fp,%hi(i)
	lui	$3,%hi(starty)
	lui	$2,%hi(board)
	sw	$23,28($sp)
	sw	$22,24($sp)
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	sw	$31,36($sp)
	sw	$21,20($sp)
	sw	$0,%lo(counter)($20)
	sw	$0,%lo(starty)($3)
	sw	$0,%lo(i)($fp)
	addiu	$23,$2,%lo(board)
	li	$17,1			# 0x1
	li	$16,100			# 0x64
	move	$18,$0
	lui	$19,%hi(z)
	li	$22,1			# 0x1
$L425:
	move	$4,$0
	j	$L426
	sw	$0,%lo(z)($19)

$L430:
	lw	$3,%lo(counter)($20)
$L442:
	lw	$2,%lo(z)($19)
	addiu	$3,$3,1
	addiu	$4,$2,1
	slt	$2,$3,8
	slt	$5,$4,8
	bne	$2,$0,$L432
	sw	$3,%lo(counter)($20)

	lui	$2,%hi(startx)
	lw	$16,%lo(startx)($2)
	addiu	$18,$18,35
	xori	$17,$17,0x1
	sw	$0,%lo(counter)($20)
$L432:
	beq	$5,$0,$L441
	sw	$4,%lo(z)($19)

$L426:
	lw	$2,%lo(i)($fp)
	xor	$3,$17,$22
	li	$8,-1			# 0xffffffffffffffff
	sll	$2,$2,3
	addu	$2,$2,$4
	sll	$2,$2,2
	addu	$2,$2,$23
	lw	$9,0($2)
	li	$2,255			# 0xff
	move	$4,$16
	addiu	$6,$16,30
	move	$5,$18
	addiu	$7,$18,30
	movn	$8,$2,$3
	sltu	$17,$17,1
	addiu	$16,$16,35
	bne	$9,$0,$L430
	lui	$21,%hi(i)

	jal	fill_rect
	nop

	j	$L442
	lw	$3,%lo(counter)($20)

$L441:
	lw	$2,%lo(i)($21)
	addiu	$2,$2,1
	slt	$3,$2,8
	bne	$3,$0,$L425
	sw	$2,%lo(i)($21)

	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$23,28($sp)
	lw	$22,24($sp)
	lw	$21,20($sp)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	drawboard
	.size	drawboard, .-drawboard
	.data
	.align	2
	.type	ion.3206, @object
	.size	ion.3206, 4
ion.3206:
	.word	1
	.local	dy.3205
	.comm	dy.3205,4,4
	.local	dx.3204
	.comm	dx.3204,4,4
	.text
	.align	2
	.globl	drawknight
	.ent	drawknight
drawknight:
	.frame	$sp,24,$31		# vars= 0, regs= 5/0, args= 0, gp= 0
	.mask	0x001f0000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-24
	sw	$20,16($sp)
	sw	$19,12($sp)
	sw	$18,8($sp)
	sw	$17,4($sp)
	sw	$16,0($sp)
	lui	$4,%hi(pos)
	lui	$2,%hi(startx)
	lui	$3,%hi(starty)
	lw	$7,%lo(startx)($2)
	lw	$24,%lo(starty)($3)
	addiu	$2,$4,%lo(pos)
	lui	$17,%hi(ion.3206)
	lui	$19,%hi(counter)
	lw	$8,4($2)
	lw	$6,%lo(pos)($4)
	lw	$15,%lo(ion.3206)($17)
	lw	$12,%lo(counter)($19)
	lui	$20,%hi(dx.3204)
	lui	$18,%hi(dy.3205)
	lui	$16,%hi(i)
	sw	$7,%lo(dx.3204)($20)
	sw	$24,%lo(dy.3205)($18)
	sw	$0,%lo(i)($16)
	move	$13,$7
	move	$5,$0
	move	$25,$0
$L444:
	move	$3,$0
	j	$L445
	move	$14,$0

$L446:
	addiu	$12,$12,1
$L458:
	addiu	$14,$3,1
	slt	$2,$12,8
	move	$3,$14
	bne	$2,$0,$L449
	addiu	$13,$13,35

	addiu	$24,$24,35
	sltu	$15,$15,1
	move	$13,$7
	move	$12,$0
$L449:
	beql	$14,$4,$L457
	addiu	$25,$5,1

$L445:
	bne	$5,$6,$L446
	li	$4,8			# 0x8

	bnel	$3,$8,$L458
	addiu	$12,$12,1

	lui	$2,%hi(data_w)
	lui	$3,%hi(data_h)
	lw	$7,%lo(data_w)($2)
	lw	$8,%lo(data_h)($3)
	lui	$2,%hi(z)
	sw	$15,%lo(ion.3206)($17)
	sw	$12,%lo(counter)($19)
	sw	$14,%lo(z)($2)
	sw	$25,%lo(i)($16)
	sw	$24,%lo(dy.3205)($18)
	sw	$13,%lo(dx.3204)($20)
	lui	$4,%hi(data_bits)
	li	$11,16711680			# 0xff0000
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	addiu	$4,$4,%lo(data_bits)
	addiu	$5,$13,-5
	move	$6,$24
	ori	$11,$11,0xffff
	move	$9,$7
	move	$10,$8
	j	draw_bitmap
	addiu	$sp,$sp,24

$L457:
	bne	$25,$4,$L444
	move	$5,$25

	lui	$2,%hi(z)
	sw	$15,%lo(ion.3206)($17)
	sw	$12,%lo(counter)($19)
	sw	$14,%lo(z)($2)
	sw	$25,%lo(i)($16)
	sw	$24,%lo(dy.3205)($18)
	sw	$13,%lo(dx.3204)($20)
	lw	$20,16($sp)
	lw	$19,12($sp)
	lw	$18,8($sp)
	lw	$17,4($sp)
	lw	$16,0($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	drawknight
	.size	drawknight, .-drawknight
	.align	2
	.globl	draw
	.ent	draw
draw:
	.frame	$sp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-8
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	addiu	$sp,$sp,-8
	sw	$31,0($sp)
	jal	drawboard
	nop

	lw	$31,0($sp)
	j	drawknight
	addiu	$sp,$sp,8

	.set	macro
	.set	reorder
	.end	draw
	.size	draw, .-draw
	.align	2
	.globl	render
	.ent	render
render:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	draw
	nop

	.set	macro
	.set	reorder
	.end	render
	.size	render, .-render
	.align	2
	.globl	logic
	.ent	logic
logic:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	logic
	.size	logic, .-logic

	.comm	board,256,4

	.comm	counter,4,4

	.comm	z,4,4

	.comm	i,4,4

	.comm	pos,8,4

	.comm	failednids,200,4

	.comm	gDetectedFirmware,4,4

	.comm	gcursor,8,4

	.comm	gpaddata,16,4

	.comm	drawframe,4,4
	.ident	"GCC: (GNU) 4.0.2 (PSPDEV 20051022)"