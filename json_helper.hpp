/*
 * Convenient helper which deals with Parson JSON library and provides JSON
 * formatted output
 */

#pragma once

#include "parson.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace mtdata_prj {
namespace json_helper {

class JsonHelper {
public:
  /** @brief Make Json From Buffer
   *  @param const char *inp_buf
   *  @return
   */
  /*
  1.
    A    :   5800 Kg
    B    :  17800 Kg
    C    :  22800 Kg
    D    :  15800 Kg
    TOTAL:  62200 Kg

  2.
    A
    5200
    Kg
    B
    17200
    Kg
    C
    22200
    Kg
    D
    15200
    Kg
    TOTAL
    59800
    Kg

  3. {
    "A": "5200Kg",
    "B": "17200Kg",
    "C": "22200Kg",
    "D": "15200Kg",
    "TOTAL": "59800Kg",
    "VALID": true
    }

*/
  void GetJsonFormattedOutput(const char *inp_buf, int inp_buf_size) {
    // get std string
    std::string inp_buf_string;
    inp_buf_string.assign(inp_buf, inp_buf_size);

    // remove all :, \, /
    std::replace(inp_buf_string.begin(), inp_buf_string.end(), ':', ' ');
    std::replace(inp_buf_string.begin(), inp_buf_string.end(), '\\', ' ');
    std::replace(inp_buf_string.begin(), inp_buf_string.end(), '/', ' ');

    // split to words
    std::string word;
    // making a string stream
    std::stringstream inp_buf_stream(inp_buf_string);

    // json serializer library init
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_json_output = NULL;

    std::vector<std::string> json_values_vector;
    // push back each word into vector
    while (inp_buf_stream >> word) {
      json_values_vector.push_back(word.c_str());
    }
    // Print Strings stored in Vector
    int sum{0};
    for (int i = 0; i < json_values_vector.size(); i = i + 3) {
      json_object_set_string(
          root_object, json_values_vector[i].c_str(),
          json_values_vector[i + 1].append(json_values_vector[i + 2]).c_str());
      if (i <= 9) {
        sum += std::atoi(json_values_vector[i + 1].c_str());
      }
    }

    // add the extra VALID field
    json_object_set_boolean(root_object, "VALID",
                            sum == std::atoi(json_values_vector[13].c_str()));

    serialized_json_output = json_serialize_to_string_pretty(root_value);
    // display the output to stderr
    std::cout << serialized_json_output << std::endl;
    // free up the json objects
    json_free_serialized_string(serialized_json_output);
    json_value_free(root_value);
  }
};

} // namespace json_helper
} // namespace mtdata_prj
