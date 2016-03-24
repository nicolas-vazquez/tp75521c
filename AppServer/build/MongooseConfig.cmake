get_filename_component (myDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set (MONGOOSE_LIBRARIES mongoose)
set (MONGOOSE_INCLUDE_DIR "/usr/local/include")

include(${myDir}/MongooseTargets.cmake)
