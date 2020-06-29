#!/bin/bash
set -e

UTHREAD_ASYNCIFY=1 scripts/fresh_build.sh
UTHREAD_CONTS=1 scripts/fresh_build.sh
UTHREAD_SERIAL=1 scripts/fresh_build.sh
