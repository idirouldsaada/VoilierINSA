@echo on & color 0A

echo off
set /P VrNvNom=Entrez le nom du nouveau projet :
set VrSimulation=_Simulation
set VrReel=_Reel


mkdir "%VrNvNom%"
xcopy /E XXX_projet "%VrNvNom%"
ren "%VrNvNom%\XXX_Projet".uvopt "%VrNvNom%".uvopt
ren "%VrNvNom%\XXX_Projet".uvproj "%VrNvNom%".uvproj
ren "%VrNvNom%\XXX_Projet%VrSimulation%".dep "%VrNvNom%%VrSimulation%".dep
ren "%VrNvNom%\XXX_Projet%VrReel%".dep "%VrNvNom%%VrReel%".dep