#!/bin/sh
# Run the project on a FreeBSD machine.

TEMP_DIR="/tmp"
TARGET_TEMP_DIR="C:\\temp"
VM_ROOT=/vms
VM_NAME=os2warp4.52

# Get the root directory of the project
PROJECT_PATH=`realpath \`dirname $0\`/../..`
PROJECT_NAME=`basename "$PROJECT_PATH"`
PROJECT_PARENT=`realpath \`dirname $0\`/../../..`

# Go to the parent directory of the project to not create relative
# paths.
cd "$PROJECT_PARENT"

# Zip
p7zip16.02_7za a "$TEMP_DIR"/"$PROJECT_NAME".zip "$PROJECT_NAME" > /dev/null

# Purge the temporary directory's contents
$VM_ROOT/control/$VM_NAME/exec.sh "delpath $TARGET_TEMP_DIR /y > JUNK"
$VM_ROOT/control/$VM_NAME/exec.sh "mkdir $TARGET_TEMP_DIR"

# Send it
$VM_ROOT/control/$VM_NAME/send.sh "$TEMP_DIR"/"$PROJECT_NAME".zip $TARGET_TEMP_DIR

# Extract it on the target
$VM_ROOT/control/$VM_NAME/exec.sh "cd $TARGET_TEMP_DIR && unzip -qq -o $TARGET_TEMP_DIR/$PROJECT_NAME.zip"

# Build it, then run tests
$VM_ROOT/control/$VM_NAME/exec.sh "cd $TARGET_TEMP_DIR\\$PROJECT_NAME && wmake -f Makefile.wat"
$VM_ROOT/control/$VM_NAME/exec.sh "cd $TARGET_TEMP_DIR\\$PROJECT_NAME && scripts\check.cmd"
