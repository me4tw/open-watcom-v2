#!/bin/sh
#
# Script to build the Open Watcom tools on Travis
# using the host platform's native C/C++ compiler.
#
# Expects 
#   - POSIX tools
#   - correct setup for all OW build environment variables
#

bootutil_proc()
{
    #
    # build new verison of wmake for host system
    #
    cd $OWSRCDIR/wmake
    mkdir $OWOBJDIR
    cd $OWOBJDIR
    rm -f $OWBINDIR/wmake
    case `uname` in
        Darwin)
            make -f ../posmake clean
            make -f ../posmake TARGETDEF=-D__OSX__
            ;;
        *)
            make -f ../posmake clean
            make -f ../posmake TARGETDEF=-D__LINUX__
            ;;
    esac
    RC=$?
    if [ $RC -eq 0 ]; then
        #
        # build new verison of builder for host system
        #
        cd $OWSRCDIR/builder
        mkdir $OWOBJDIR
        cd $OWOBJDIR
        rm -f $OWBINDIR/builder
        $OWBINDIR/wmake -f ../binmake clean
        $OWBINDIR/wmake -f ../binmake bootstrap=1 builder.exe
        RC=$?
    fi
}

build_proc()
{
    if [ "$TRAVIS_BRANCH" = "$OWBRANCH" ]; then
        if [ "$TRAVIS_EVENT_TYPE" = "pull_request" ]; then
            if [ "$1" = "build" ]; then
                bootutil_proc
                if [ $RC -eq 0 ]; then
                    cd $OWSRCDIR
                    builder boot
                    RC=$?
                    if [ $RC -eq 0 ]; then
                        cd $OWSRCDIR
                        builder
                        RC=$?
                    fi
                fi
            else
                RC=0
            fi
        else
            if [ "$1" = "boot" ]; then
                bootutil_proc
                if [ $RC -eq 0 ]; then
                    cd $OWSRCDIR
                    builder -q boot
                    RC=$?
                fi
            else
                cd $OWSRCDIR
                if [ "$1" = "build" ]; then
                    builder -q build
                elif [ "$1" = "docpdf" ]; then
                    builder docpdf
                else
                    builder -q $1
                fi
                RC=$?
            fi
        fi
    elif [ "$TRAVIS_BRANCH" = "$OWBRANCH_COVERITY" ]; then
        if [ "$TRAVIS_EVENT_TYPE" = "cron" ]; then
            RC=0
        elif [ "$TRAVIS_EVENT_TYPE" = "push" ]; then
            if [ "$1" = "build" ]; then
                travis/covscan.sh
            else
                RC=0
            fi
        else
            RC=0
        fi
    else
        RC=0
    fi
    cd $OWROOT
    return $RC
}

build_proc $*
