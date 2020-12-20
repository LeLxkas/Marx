#pragma once

#define MX_THROW_EXCEPT(msg) throw ::Marx::MarxException(__LINE__, __FILE__, msg)
#define MX_THROW_EXCEPT_INFO(msg, errCode) throw ::Marx::MarxExceptionInfo(__LINE__, __FILE__, msg, errCode)

#ifdef MX_USE_CONDITIONAL_EXCEPT
  #define MX_VERIFY_THROW(r, msg) { if (!(r)) MX_THROW_EXCEPT(msg); }
  #define MX_VERIFY_THROW_INFO(r, msg) { if (!(r)) MX_THROW_EXCEPT_INFO(msg, GetLastError()); }
#else
  #define MX_VERIFY_EXCEPT(r, msg) r
  #define MX_VERIFY_THROW_INFO(r, msg) r
#endif