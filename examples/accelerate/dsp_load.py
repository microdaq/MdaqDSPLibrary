# This file is subject to the terms and conditions defined in
# file 'LICENSE.md', which is part of this source code package.
# Embedded-solutions 2020, www.microdaq.org


import os
import microdaq

mdaq = microdaq.Device("10.10.1.1")
mdaq.dsp_init(os.path.join("", "accelerate.out"), 100, 5)
mdaq.dsp_start()
