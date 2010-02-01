// xcom_ptr.h
// DirectX dynamic objects smart pointer class definition.
// Vladimir Rutsky <altsysrq@gmail.com>
// 09.09.2009

#ifndef XCOM_PTR_H
#define XCOM_PTR_H

namespace xcg
{
  template< class T >
  struct com_ptr
  {
    com_ptr()
      : ptr_(0)
    {}
    
    com_ptr( T *ptr )
      : ptr_(ptr)
    {}
    
    ~com_ptr()
    {
      if (ptr_ != 0)
        ptr_->Release();
    }
    
    operator bool () const
    {
      return (ptr_ != 0);
    }
    
    T * get()
    {
      return ptr_;
    }
    
    T * operator -> ()
    {
      return ptr_;
    }
    
    void reset( T *newPtr = 0 )
    {
      if (ptr_ != 0)
        ptr_->Release();
      ptr_ = newPtr;
    }
    
  private:
    T *ptr_;
  };
} // End of namespace 'xcg'

#endif // XCOM_PTR_H
