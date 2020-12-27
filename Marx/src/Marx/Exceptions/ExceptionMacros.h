#pragma once

#define MX_THROW_EXCEPT(msg) throw ::Marx::MarxException(__LINE__, __FILE__, msg)
#define MX_THROW_EXCEPT_INFO(msg, errCode) throw ::Marx::MarxExceptionInfo(__LINE__, __FILE__, msg, errCode)
#define MX_THROW_EXCEPT_HR(hr) throw ::Marx::HrException(__LINE__, __FILE__, hr)
#define MX_THROW_EXCEPT_HR_INFO(hr) throw :: Marx::HrInfoException(__LINE__, __FILE__, hr, Marx::DX11InfoManager::get()->getMessages())

#ifdef MX_USE_CONDITIONAL_EXCEPT
  #define MX_VERIFY_THROW(r, msg) { if (!(r)) MX_THROW_EXCEPT(msg); }
  #define MX_VERIFY_THROW_INFO(r, msg) { if (!(r)) MX_THROW_EXCEPT_INFO(msg, GetLastError()); }
  // Scope needs to have HRESULT hr defined
  #define MX_DEBUG_HR_DECL HRESULT hr
  #define MX_VERIFY_THROW_HR(r) { if (FAILED(hr = (r))) MX_THROW_EXCEPT_HR(hr); }
  #define MX_VERIFY_THROW_HR_INFO(r) { Marx::DX11InfoManager::get()->set(); if (FAILED(hr = (r))) MX_THROW_EXCEPT_HR_INFO(hr); }
#else
  #define MX_VERIFY_EXCEPT(r, msg) r
  #define MX_VERIFY_THROW_INFO(r, msg) r
  #define MX_DEBUG_HR_DECL
  #define MX_VERIFY_THROW_HR(r) r
  #define MX_VERIFY_THROW_HR_INFO(r) r
#endif