#!/bin/sh
# Run the project on a FreeBSD machine.

TEMP_DIR="/tmp"
TARGET_TEMP_DIR="/tmp"
VM_ROOT=/vms
VM_NAME=freebsd13.1

# Get the root directory of the project
PROJECT_PATH=`realpath \`dirname $0\`/../..`
PROJECT_NAME=`basename "$PROJECT_PATH"`
PROJECT_PARENT=`realpath \`dirname $0\`/../../..`

# Go to the parent directory of the project to not create relative
# paths.
cd "$PROJECT_PARENT"

# Tar up the project
tar -cvf "$TEMP_DIR"/"$PROJECT_NAME".tar --exclude-vcs "$PROJECT_NAME" > /dev/null

# Purge the temporary directory's contents
$VM_ROOT/control/$VM_NAME/exec.sh "rm -rf /tmp/*"

# Send it
$VM_ROOT/control/$VM_NAME/send.sh "$TEMP_DIR"/"$PROJECT_NAME".tar $TARGET_TEMP_DIR

# Extract it on the target
$VM_ROOT/control/$VM_NAME/exec.sh "cd $TARGET_TEMP_DIR; tar -xf $TARGET_TEMP_DIR/$PROJECT_NAME.tar"

# Build it, then run tests
$VM_ROOT/control/$VM_NAME/exec.sh "cd $TARGET_TEMP_DIR/$PROJECT_NAME; make -f Makefile.nix; ./scripts/check.sh"
