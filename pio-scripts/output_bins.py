Import('env')
import os
import shutil
import gzip
from datetime import datetime

OUTPUT_DIR = "build_output"
now_time_str = datetime.now().strftime("%Y-%m-%d-%H-%M-%S")

def _create_dirs(dirs=["firmware", "map"]):
    # check if output directories exist and create if necessary
    if not os.path.isdir(OUTPUT_DIR):
        os.mkdir(OUTPUT_DIR)

def bin_rename_copy(source, target, env):
    _create_dirs()
    # create string with location and file names based on variant

    bin_file = "{}{}firmware-{}.bin".format(OUTPUT_DIR, os.path.sep,now_time_str)
    # copy firmware.bin to firmware/<variant>.bin
    shutil.copy(".pio/build/esp12e/firmware.bin", bin_file)


def bin_gzip(source, target, env):
    _create_dirs()
    # create string with location and file names based on variant
    bin_file = "{}{}firmware-{}.bin".format(OUTPUT_DIR, os.path.sep,now_time_str)
    gzip_file = "{}{}firmware-{}.bin.gz".format(OUTPUT_DIR, os.path.sep,now_time_str)

    # check if new target files exist and remove if necessary
    if os.path.isfile(gzip_file): os.remove(gzip_file)

    # write gzip firmware file
    with open(bin_file,"rb") as fp:
        with gzip.open(gzip_file, "wb", compresslevel = 9) as f:
            shutil.copyfileobj(fp, f)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", [bin_rename_copy, bin_gzip])
