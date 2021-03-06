# Auto-generated by E0clipseNSIS Script Wizard
# 06.09.2010 11:45:57

Name "The Wheat Snooper"
SetCompressor lzma
# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
!define VERSION 2.0
!define COMPANY Lookias
!define URL http://lookias.worms2d.info/

# Included files
!include Sections.nsh

# Reserved Files
ReserveFile "${NSISDIR}\Plugins\StartMenu.dll"

# Variables
Var StartMenuGroup

# Installer pages
Page license
Page directory
Page custom StartMenuGroupSelect "" ": Start Menu Folder"
Page instfiles

# Installer attributes
OutFile "TheWheatSnooperwin32.exe"
InstallDir "$PROGRAMFILES\The Wheat Snooper"
CRCCheck on
XPStyle on
Icon TheWheatSnooper\pictures\tray.ico
ShowInstDetails show
AutoCloseWindow false
LicenseForceSelection radiobuttons
LicenseData TheWheatSnooper\license\gplv2_opening.txt
VIProductVersion 2.0.0.0
VIAddVersionKey ProductName "The Wheat Snooper"
VIAddVersionKey ProductVersion "${VERSION}"
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion "${VERSION}"
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
UninstallIcon "${NSISDIR}\Contrib\Graphics\Icons\classic-uninstall.ico"
ShowUninstDetails show

DirText "If you allready have an installation of this programm, \ 
        you can simply overwrite it with the new Snooper, your settings inside the snpini will be kept. $\n\
        Note: Only the existing files inside the snpini folder will be kept."

# Installer sections
!macro CREATE_SMGROUP_SHORTCUT NAME PATH
    Push "${NAME}"
    Push "${PATH}"
    Call CreateSMGroupShortcut	
!macroend

Section -Main SEC0000
	KillProcDLL::KillProc "TheWheatSnooper.exe"	
	sleep 1000
    SetOutPath $INSTDIR
    SetOverwrite on
    File /r /x snpini /x query /x .svn /x lastedited.textscheme TheWheatSnooper\*
    WriteRegStr HKLM "${REGKEY}\Components" Main 1
SectionEnd

Section -post SEC0001    
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    WriteRegStr HKLM "${REGKEY}" StartMenuGroup $StartMenuGroup
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro CREATE_SMGROUP_SHORTCUT "Uninstall $(^Name)" $INSTDIR\uninstall.exe       
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1     
             
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
!macro DELETE_SMGROUP_SHORTCUT NAME
    Push "${NAME}"
    Call un.DeleteSMGroupShortcut
!macroend

Section /o -un.Main UNSEC0000
    RmDir /r /REBOOTOK $INSTDIR
    DeleteRegValue HKLM "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    !insertmacro DELETE_SMGROUP_SHORTCUT "Uninstall $(^Name)"
    Delete /REBOOTOK "$INSTDIR\uninstall.exe"    
    Delete /REBOOTOK "$LOCALAPPDATA\VirtualStore\Program Files\The Wheat Snooper\snpini\*"
    Delete /REBOOTOK "$LOCALAPPDATA\VirtualStore\Program Files\The Wheat Snooper\query\*"
    Delete /REBOOTOK "$LOCALAPPDATA\VirtualStore\Program Files\The Wheat Snooper\*"
    RmDir /REBOOTOK "$LOCALAPPDATA\VirtualStore\Program Files\The Wheat Snooper"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\*"
    RmDir /REBOOTOK "$SMPROGRAMS\$StartMenuGroup"
    Delete /REBOOTOK "$DESKTOP\The Wheat Snooper.lnk"        
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"    
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd
  
# Installer functions
Function StartMenuGroupSelect    
    Push $R1
    StartMenu::Select /checknoshortcuts "Do not create shortcuts" /autoadd /text "Select the Start Menu folder in which to create the program's shortcuts:" /lastused $StartMenuGroup "The Wheat Snooper"
    Pop $R1
    StrCmp $R1 success success
    StrCmp $R1 cancel done
    MessageBox MB_OK $R1
    Goto done
success:
    Pop $StartMenuGroup
done:
    Pop $R1
FunctionEnd

Function .onInit
    InitPluginsDir
FunctionEnd

Function CreateSMGroupShortcut   
    Exch $R0 ;PATH
    Exch
    Exch $R1 ;NAME
    Push $R2
    StrCpy $R2 $StartMenuGroup 1
    StrCmp $R2 ">" no_smgroup
    SetOutPath $INSTDIR
    CreateShortCut "$DESKTOP\The Wheat Snooper.lnk" "$INSTDIR\TheWheatSnooper.exe" "" "$INSTDIR\pictures\tray.ico"
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$R1.lnk" $R0
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\The Wheat Snooper.lnk" $INSTDIR\TheWheatSnooper.exe "" "$INSTDIR\pictures\tray.ico"
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Homepage of $(^Name).lnk" http://lookias.worms2d.info/forum/viewforum.php?f=9
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Tutorial of $(^Name).lnk" http://lookias.worms2d.info/tutorial.html    
no_smgroup:
    Pop $R2
    Pop $R1
    Pop $R0
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    ReadRegStr $StartMenuGroup HKLM "${REGKEY}" StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}   
FunctionEnd

Function un.DeleteSMGroupShortcut
    Exch $R1 ;NAME
    Push $R2
    StrCpy $R2 $StartMenuGroup 1
    StrCmp $R2 ">" no_smgroup    
no_smgroup:
    Pop $R2
    Pop $R1
FunctionEnd

