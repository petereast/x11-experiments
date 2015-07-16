#! /bin/sh

## compile.sh -- This should compile the X11 stuff nicely

##TODO: Do a g++ compile of everything *.cpp that can be found

for directory in $(ls -R -1 -B -U -L | grep ":" | awk '{gsub(":", "/"); print}')
	do
		for filename in $(ls $directory -B -1 | grep ".cpp")
			do
				target="$directory$filename"
				g++ -Wall $target  -lX11 -o "$directory"out >> "${directory}compile.log"
				echo "Built $target\nOutput to ${directory}out";
	done
done


##TODO: Do a git commit/push to the branch minutely_build

git add .

git commit --message="Automated git update commital"

git push origin HEAD:minutely_build

clear && echo "Automated build and commit complete"
