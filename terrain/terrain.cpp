// terrain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ncl/gl/GlfwApp.h>
#include "TerrainScene.h"

static ConsoleAppender CONSOLE_APPENDER;
static FileAppender FILE_APPENDER("log.txt");


vector<Appender*> Logger::appenders = { &CONSOLE_APPENDER,  &FILE_APPENDER };
const unsigned int Logger::level = LEVEL_DEBUG;

int main()
{
	Scene* scene = new TerrainScene;
	start(scene);
    return 0;
}

