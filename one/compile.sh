#! /bin/sh

## compile.sh -- This should compile the X11 stuff nicely

##TODO: Do a g++ compile of everything *.cpp that can be found

for filename in $(ls -R | grep ".cpp") 
	do
		g++ -I /usr/X11/include -L /usr/X11/lib -o output $filename -lX11

done


##TODO: Do a git commit/push to the branch minutely_build

git add .

git commit --message="Automated git update commital"

git push origin HEAD:minutely_build
