git add .
git commit -m "commit `date '+%Y-%m-%d'`"
git push -u origin master --tags
git status

exit

git config --global --unset-all credential.helper
git config --unset-all credential.helper
git config --system --unset-all credential.helper



git init
git add phpDaemon.c
git add phpDaemon.conf
git add Makefile
git add README.md
git commit -m "first commit"
git remote add origin http://code.pick-nik.ru/Petr/phpdaemon.git
git push -u origin master

exit

git init
git remote add origin http://code.pick-nik.ru/Petr/phpdaemon.git
git add phpDaemon.c
git add phpDaemon.conf
git add Makefile
git add README.md
git commit -m "commit src `date '+%x'`"
#git symbolic-ref HEAD refs/heads/master
git push -u origin master
git status
