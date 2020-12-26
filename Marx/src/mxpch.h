#pragma once

// General headers
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <optional>

#include <string>
#include <sstream>
#include <vector>

#include <stdexcept>

#include "Marx/Log.h"

// Windows specific headers
#ifdef MX_PLATFORM_WINDOWS
  #include <Windows.h>
  #include <wrl.h>
  #include <d3d11.h>
#endif