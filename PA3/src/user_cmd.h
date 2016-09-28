// **************************************************************************
// File       [ test_cmd.h ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************

#ifndef _TEST_CMD_H_
#define _TEST_CMD_H_

#include "../lib/cmd.h"

class TestCmd : public CommonNs::Cmd {
public:
         TestCmd(const char * const name);
         ~TestCmd();

    bool exec(int argc, char **argv);
};

class Read_GraphCmd : public CommonNs::Cmd {
public:
         Read_GraphCmd(const char * const name);
         ~Read_GraphCmd();

    bool exec(int argc, char **argv);
};

class Write_Tree_DFSCmd : public CommonNs::Cmd {
public:
         Write_Tree_DFSCmd(const char * const name);
         ~Write_Tree_DFSCmd();

    bool exec(int argc, char **argv);
};

class Write_Tree_BFSCmd : public CommonNs::Cmd {
public:
         Write_Tree_BFSCmd(const char * const name);
         ~Write_Tree_BFSCmd();

    bool exec(int argc, char **argv);
};

class Write_DijkstraCmd : public CommonNs::Cmd {
public:
         Write_DijkstraCmd(const char * const name);
         ~Write_DijkstraCmd();

    bool exec(int argc, char **argv);
};

#endif

