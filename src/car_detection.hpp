/*
// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <vector>
#include <gflags/gflags.h>
#include <iostream>

#ifdef _WIN32
#include <os/windows/w_dirent.h>
#else
#include <dirent.h>
#endif

/// @brief message for help argument
static const char help_message[] = "Print a usage message.";

/// @brief message for images argument
static const char video_message[] = "Optional. Path to an video file. Default value is \"cam\" to work with camera.";

/// @brief message for model argument
static const char vehicle_detection_model_message[] = "Required. Path to the Vehicle/License-Plate Detection model (.xml) file.";
static const char vehicle_attribs_model_message[] = "Optional. Path to the Vehicle Attributes model (.xml) file.";

/// @brief message for assigning vehicle detection inference to device
static const char target_device_message[] = "Specify the target device for Vehicle Detection (CPU, GPU, FPGA, MYRIAD, or HETERO). ";

/// @brief message for number of simultaneously vehicle detections using dynamic batch
static const char num_batch_message[] = "Specify number of maximum simultaneously processed frames for Vehicle Detection ( default is 1).";

/// @brief message for assigning vehicle attributes to device
static const char target_device_message_vehicle_attribs[] = "Specify the target device for Vehicle Attributes (CPU, GPU, FPGA, MYRIAD, or HETERO). ";

/// @brief message for number of simultaneously vehicle attributes detections using dynamic batch
static const char num_batch_va_message[] = "Specify number of maximum simultaneously processed vehicles for Vehicle Attributes Detection ( default is 1).";

/// @brief message for enabling dynamic batching for vehicle detections
static const char dyn_va_message[] = "Enable dynamic batching for Vehicle Attributes Detection ( default is 0).";

/// @brief message auto_resize input flag
static const char auto_resize_message[] = "Enable auto-resize (ROI crop & data resize) of input during inference.";

/// @brief message for performance counters
static const char performance_counter_message[] = "Enables per-layer performance statistics.";

/// @brief message for clDNN custom kernels desc
static const char custom_cldnn_message[] = "For clDNN (GPU)-targeted custom kernels, if any. "\
"Absolute path to the xml file with the kernels desc.";

/// @brief message for user library argument
static const char custom_cpu_library_message[] = "For MKLDNN (CPU)-targeted custom layers, if any. " \
"Absolute path to a shared library with the kernels impl.";

/// @brief message for probability threshold argument
static const char thresh_output_message[] = "Probability threshold for vehicle/licence-plate detections.";

/// @brief message raw output flag
static const char raw_output_message[] = "Output Inference results as raw values.";

/// @brief message async function flag
static const char async_depth_message[] = "Maximum number of outstanding async API calls allowed (1=synchronous=default, >1=asynchronous).";

/// @brief message no wait for keypress after input stream completed
static const char no_wait_for_keypress_message[] = "No wait for key press in the end.";

/// @brief message no show processed video
static const char no_show_processed_video[] = "No show processed video.";

/// \brief Define flag for showing help message <br>
DEFINE_bool(h, false, help_message);

/// \brief Define parameter for set image file <br>
/// It is a required parameter
DEFINE_string(i, "cam", video_message);

/// \brief Define parameter for vehicle detection  model file <br>
/// It is a required parameter
DEFINE_string(m, "", vehicle_detection_model_message);

/// \brief Define parameter for vehicle attributes model file <br>
/// It is a required parameter
DEFINE_string(m_va, "", vehicle_attribs_model_message);

/// \brief device the target device for vehicle detection infer on <br>
DEFINE_string(d, "CPU", target_device_message);

/// \brief batch size for running vehicle detection <br>
DEFINE_uint32(n, 1, num_batch_message);

/// \brief device the target device for vehicle attributes detection on <br>
DEFINE_string(d_va, "CPU", target_device_message_vehicle_attribs);

/// \brief batch size for running vehicle attributes detection <br>
DEFINE_uint32(n_va, 1, num_batch_va_message);

/// \brief Define flag for enabling dynamic batching for vehicle attributes detection <br>
DEFINE_bool(dyn_va, false, dyn_va_message);

/// \brief Define flag for enabling auto-resize of inputs for all models <br>
DEFINE_bool(auto_resize, false, auto_resize_message);

/// \brief Enable per-layer performance report
DEFINE_bool(pc, false, performance_counter_message);

/// @brief clDNN custom kernels path <br>
/// Default is ./lib
DEFINE_string(c, "", custom_cldnn_message);

/// @brief Absolute path to CPU library with user layers <br>
/// It is a optional parameter
DEFINE_string(l, "", custom_cpu_library_message);

/// \brief Flag to output raw scoring results<br>
/// It is an optional parameter
DEFINE_bool(r, false, raw_output_message);

/// \brief Flag to output raw scoring results<br>
/// It is an optional parameter
DEFINE_double(t, 0.5, thresh_output_message);

/// \brief Flag to disable keypress exit<br>
/// It is an optional parameter
DEFINE_bool(no_wait, false, no_wait_for_keypress_message);

/// \brief Flag to disable processed video showing<br>
/// It is an optional parameter
DEFINE_bool(no_show, false, no_show_processed_video);

/// \brief parameter to set depth (number of outstanding requests) of asynchronous API calls <br>
/// It is an optional parameter
DEFINE_uint32(n_async, 1, async_depth_message);

/**
* \brief This function show a help message
*/
static void showUsage() {
    std::cout << std::endl;
    std::cout << "car_detection_tutorial [OPTION]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "    -h                         " << help_message << std::endl;
    std::cout << "    -i \"<path>\"              " << video_message << std::endl;
    std::cout << "    -m \"<path>\"              " << vehicle_detection_model_message<< std::endl;
    std::cout << "    -m_va \"<path>\"           " << vehicle_attribs_model_message << std::endl;
    std::cout << "      -l \"<absolute_path>\"   " << custom_cpu_library_message << std::endl;
    std::cout << "          Or" << std::endl;
    std::cout << "      -c \"<absolute_path>\"   " << custom_cldnn_message << std::endl;
    std::cout << "    -d \"<device>\"            " << target_device_message << std::endl;
    std::cout << "    -n \"<num>\"               " << num_batch_message << std::endl;
    std::cout << "    -d_va \"<device>\"         " << target_device_message_vehicle_attribs << std::endl;
    std::cout << "    -n_va \"<num>\"            " << num_batch_va_message << std::endl;
    std::cout << "    -dyn_va                    " << dyn_va_message << std::endl;
    std::cout << "    -n_aysnc \"<num>\"         " << async_depth_message << std::endl;
    std::cout << "    -auto_resize               " << auto_resize_message << std::endl;
    std::cout << "    -no_wait                   " << no_wait_for_keypress_message << std::endl;
    std::cout << "    -no_show                   " << no_show_processed_video << std::endl;
    std::cout << "    -pc                        " << performance_counter_message << std::endl;
    std::cout << "    -r                         " << raw_output_message << std::endl;
    std::cout << "    -t                         " << thresh_output_message << std::endl;
}
