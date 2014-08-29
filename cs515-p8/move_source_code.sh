#! /bin/bash

while getopts ":d:" opt; do
	case $opt in
	d)
		mkdir $OPTARG

		cp -r error.cpp \
			 error.h \
			Makefile \
			gpl_assert.cpp\
			gpl_assert.h\
			gpl.cpp\
			gpl.l\
			gpl_type.cpp\
			gpl_type.h\
			gpl.y\
			indent.cpp\
			indent.h\
			parser.h\
			symbol_table.cpp\
			symbol_table.h\
			variable.cpp\
			variable.h\
			expression.cpp\
			expression.h\
			globals.cpp\
			globals.h\
			animation_block.cpp\
			animation_block.h\
			circle.cpp\
			circle.h\
			default_pixmap.h\
			event_manager.cpp\
			event_manager.h\
			game_object.cpp\
			game_object.h\
			pixmap.cpp\
			pixmap.h\
			rectangle.cpp\
			rectangle.h\
			statement_block.cpp\
			statement_block.h\
			textbox.cpp\
			textbox.h\
			triangle.cpp\
			triangle.h\
			window.cpp\
			window.h\
			src/\
			include/\
			$OPTARG	

			echo "Moved::: 
			error.cpp
			error.h

			Makefile

			gpl_assert.cpp
			gpl_assert.h
			gpl.cpp
			gpl.l
			gpl_type.cpp
			gpl_type.h
			gpl.y
			indent.cpp
			indent.h
			parser.h

			symbol_table.cpp
			symbol_table.h
			variable.cpp
			variable.h
			expression.cpp
			expression.h
			globals.cpp
			globals.h

			animation_block.cpp
			animation_block.h
			circle.cpp
			circle.h
			default_pixmap.h
			event_manager.cpp
			event_manager.h
			game_object.cpp
			game_object.h
			pixmap.cpp
			pixmap.h
			rectangle.cpp
			rectangle.h
			statement_block.cpp
			statement_block.h
			textbox.cpp
			textbox.h
			triangle.cpp
			triangle.h
			window.cpp
			window.h
			src/
			include/

			TO:::
			-$OPTARG
			"
			;;
	\?)		
		echo "Nothing has been done..."
	;;
	esac
done
