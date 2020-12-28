#pragma once

#define MX_THROW_EXCEPT_HR_INFO(hr) throw :: Marx::HrInfoException(__LINE__, __FILE__, hr, Marx::DX11InfoManager::get()->getMessages())

#ifdef MX_USE_CONDITIONAL_EXCEPT
  // Scope must have HRESULT hr definded
  #define MX_VERIFY_THROW_HR_INFO(r) { Marx::DX11InfoManager::get()->set(); if (FAILED(hr = (r))) MX_THROW_EXCEPT_HR_INFO(hr); }
#else
  #define MX_VERIFY_THROW_HR_INFO(r) r
#endif