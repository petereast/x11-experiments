#! /bin/sh

## compile.sh -- This should compile the X11 stuff nicely

##TODO: Do a g++ compile of everything *.cpp that can be found
##DONE

for directory in $(ls -R -1 -B -U -L | grep ":" | awk '{gsub(":", "/"); print}')
	do
		for filename in $(ls $directory -B -1 | grep ".cpp")
			do
				target="$directory$filename"
				$(g++  $target -lX11 -o "$directory"out )| grep "error" | echo
				echo "Built $target\nOutput to ${directory}out";
	done
done


##TODO: Do a git commit/push to the branch minutely_build

# Stage all the files to git
git add . --all

# Commit those files
git commit --message="Automated git update commital"

#you guessed it, push those files to a seperate branch to the main code repo
git push origin HEAD:minutely_build

clear && echo "Automated build and commit complete"
