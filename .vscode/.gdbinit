python

import sys
import os
for path in os.getenv("PATH").split(';'):
  sys.path.append(path)

from libcxx_printers import register_libcxx_printer_loader
register_libcxx_printer_loader()

end