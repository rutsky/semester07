#ifndef UMP_FVF_GEN_H
#define UMP_FVF_GEN_H

//  Copyright (C) 2000 by Vesa Karvonen. All rights reserved.
//
//  Permission is granted to freely use this software as long as this
//  copyright message is retained.
//
//  September 30. 2000.

#include <boost/static_assert.hpp>

#include <d3d9.h>

namespace D3D_Util
{

//  Flexible Vertex Format Generator
//  ================================
//  
//  Direct3D Immediate Mode uses flag values to describe vertex formats
//  used for DrawPrimitive-based rendering. Each combination of these
//  flexible vertex format (FVF) flags corresponds to a vertex type.
//  Traditionally the programmer has manually translated FVF codes into C++
//  structures. For example the FVF code:
//  
//      const DWORD my_vertex_format =
//          D3DFVF_XYZ    |
//          D3DFVF_NORMAL |
//          D3DFVF_TEX1   ;
//  
//  corresponds to the following structure:
//  
//      struct My_Vertex_Type
//      {
//          float m_pos[3];
//          float m_normal[3];
//          float m_tex_1[2];
//      };
//  
//  The C++ language features make it possible to automate this process,
//  so that the vertex type is generated by the compiler. Using the
//  FVF_Gen<> metaprogram, a vertex type, (nearly) equivalent to the above
//  structure, can be obtained simply by giving the FVF code to the
//  generator:
//  
//      typedef FVF_Gen<my_vertex_format>::Res My_Vertex_Type;
//  
//  The most notable difference to a hand written vertex structure is that
//  the generated vertex type is not a POD structure and therefore can not
//  be initialized with an aggregate initializer.
//  
//  It is possible to parametrize the generator so that the user can choose
//  the names and types of each possible vertex member. Unfortunately at
//  least the Visual C++ 6 compiler gives an internal compiler error when
//  that feature is enabled. (You can of course use some workaround. Most
//  such workarounds are rather cumbersome to use.)
//  
//  Although the generator was originally implemented mostly for fun it is
//  not just a toy. Using the generator has a number of benefits:
//  - it saves you from typing vertex structures explicitly
//  - it allows you to localize changes to vertex formats better
//  - it contains the rules for translating an FVF code into a vertex type
//    and you don't have to learn or remember them anymore
//  
//  I should point out that because the generator works by concatenating
//  classes using parametrized multiple inheritance there is no C++ standard
//  imposed guarantee on the layout of the resulting type. In practise on
//  Visual C++ 6 and most other compilers the layout will be exactly as
//  designed.
//  
//  How does it work?
//  =================
//  
//  First the bits of the FVF code are interpreted using the D3DFVF macros.
//  After the interpretation, we have a set of boolean and integer constants
//  that describe the vertex format conveniently.
//  
//      enum
//      {
//          has_pos    = /*...*/,
//          has_rhw    = /*...*/,
//          has_normal = /*...*/,
//          // ...
//      };
//  
//  Then the generator uses a Config trait class to generate the required
//  element types. For instance, a vertex may contain 0 to 5 blending
//  weights. The generator uses the trait class to generate blending weight
//  element with the appropriate number of weights.
//  
//  Finally the generator concatenates the generated elements into a vertex
//  one-by-one using parameterized multiple inheritance. Only the elements
//  that were specified in the FVF code are concatenated into the resulting
//  vertex type. The final result is a simple inheritance cascade with the
//  required elements.
//  
//  For example, the FVF code (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)
//  yeilds the type Both<Both<Pos,Normal>,Tex_1>, whose inheritance
//  hierarchy looks like this:
//  
//      Pos          Normal
//       A             A
//       |             |
//       +------+------+
//              |
//      Both<Pos,Normal>   Tex_1
//              A             A
//              |             |
//              +------+------+
//                     |
//         Both<Both<Pos,Normal>,Tex_1>
//  
//  The generator also checks that the FVF code is valid and that the
//  various elements of the vertex seem appropriate.
//  
//  Customizing the generated vertex
//  ================================
//  
//  You can customize the Config trait class, so that you'll get the desired
//  kind of elements in your vertices. Suppose you want that your vertices
//  have float fields x, y, z for the position and a D3DVECTOR normal for
//  the normal - a weird configuration. You can accomplish this by using the
//  following definitions in the Config class:
//  
//      struct Default_FVF_Gen_Config
//      {
//          struct Pos    {float x, y, z;};
//          // ...
//          struct Normal {D3DVECTOR normal;};
//          // ...
//      };
//  
//  Bibliography
//  ============
//  
//  If you are interested in metaprogramming, you can find some information
//  here:
//  
//  http://extreme.indiana.edu/~tveldhui/papers/Template-Metaprograms/meta-art.html

//#define UMP_META_ASSERT(condition)\
//    typedef bool Meta_Assertion[2 * !!(condition) - 1]
#define UMP_META_ASSERT(condition) BOOST_STATIC_ASSERT(condition)

//  Disables the annoying "Truncated to 255 characters" warning
#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

//  Meta-If implementation
template<bool>
struct Select
{
    template<class T0, class T1>
    struct Type
    {
        typedef T1 Res;
    };
};

template<>
struct Select<true>
{
    template<class T0, class T1>
    struct Type
    {
        typedef T0 Res;
    };
};

template<bool i, class T0, class T1>
struct If
{
    typedef typename Select<i>::template Type<T0,T1>::Res Res;
};

template<class T>
struct Is_Void
{
    enum {res = false};
};

template<>
struct Is_Void<void>
{
    enum {res = true};
};

//  Type catenator
template<class B0, class B1>
struct Both : B0, B1
{
};

template<class B0, class B1>
class Cat
{
    typedef typename If<Is_Void<B0>::res, B1, B0>::Res T0;
    typedef typename If<Is_Void<B0>::res, void, B1>::Res T1;
public:
    typedef typename If<Is_Void<T1>::res, T0, Both<T0,T1> >::Res Res;

private:
    typedef typename If<Is_Void<T1>::res, int, T1>::Res Checked_T1;

    UMP_META_ASSERT(
        Is_Void<T1>::res ||
        sizeof(Res) == sizeof(T0)+sizeof(Checked_T1));
};

//  Conditional catenator
template<bool condition, class B0, class B1>
class Cat_If
{
    typedef typename Cat<B0, B1>::Res Both;
public:
    typedef typename If<condition, Both, B0>::Res Res;
};

//  This trait class is used for configuring the FVF generator.
struct Default_FVF_Gen_Config
{
    struct Pos          {float m_pos[3];};
    struct RHW          {float m_rhw;};
    template<int n>
    struct Weights_Gen  {float m_weights[n]; typedef Weights_Gen<n> Res;};
    struct Normal       {float m_normal[3];};
    struct Diffuse      {DWORD m_diffuse;};
    struct Specular     {DWORD m_specular;};
    template<int n>
    struct Tex_1_Gen    {float m_tex_1[n]; typedef Tex_1_Gen<n> Res;};
    template<int n>
    struct Tex_2_Gen    {float m_tex_2[n]; typedef Tex_2_Gen<n> Res;};
    template<int n>
    struct Tex_3_Gen    {float m_tex_3[n]; typedef Tex_3_Gen<n> Res;};
    template<int n>
    struct Tex_4_Gen    {float m_tex_4[n]; typedef Tex_4_Gen<n> Res;};
};

//  This metaprogram generates a vertex structure according to the specified
//  D3D Flexible Vertex Format code. This implementation handles only up to
//  4 texture coordinate sets. Furthermore, under Visual Studio 6 or earlier
//  the configuration feature does not compile.
template<DWORD fvf, class Config = Default_FVF_Gen_Config>
class FVF_Gen
{
#if defined(_MSC_VER) && _MSC_VER <= 1200   //  Optimistic???
    typedef Default_FVF_Gen_Config Config;
#endif

    enum
    {
        dummy           = 1,

        has_pos         = (fvf & D3DFVF_POSITION_MASK) != 0,
        has_rhw         = (fvf & D3DFVF_POSITION_MASK) == D3DFVF_XYZRHW,
        has_weights     = (fvf & D3DFVF_POSITION_MASK) >= D3DFVF_XYZB1,
        num_weights     = has_weights
                            ? (fvf-D3DFVF_XYZB1 & D3DFVF_POSITION_MASK) >> 1
                            : dummy,
        has_normal      = !!(fvf & D3DFVF_NORMAL),
        has_diffuse     = !!(fvf & D3DFVF_DIFFUSE),
        has_specular    = !!(fvf & D3DFVF_SPECULAR),
        has_tex_coords  = !!(fvf & D3DFVF_TEXCOUNT_MASK),
        num_tex_coords  = (fvf&D3DFVF_TEXCOUNT_MASK)>>D3DFVF_TEXCOUNT_SHIFT,

#define UMP_DIM_TEX(i) ((0x1432 >> ((fvf >> ((i) * 2 + 14)) & 0xC)) & 0xF)

        dim_tex_1       = UMP_DIM_TEX(1) ? UMP_DIM_TEX(1) : dummy,
        dim_tex_2       = UMP_DIM_TEX(2) ? UMP_DIM_TEX(2) : dummy,
        dim_tex_3       = UMP_DIM_TEX(3) ? UMP_DIM_TEX(3) : dummy,
        dim_tex_4       = UMP_DIM_TEX(4) ? UMP_DIM_TEX(4) : dummy,

#undef UMP_DIM_TEX

        is_valid        =
            has_pos &&
            (has_normal || has_diffuse || has_specular || has_tex_coords) &&
            !(has_rhw && (has_normal || has_weights))
    };

    UMP_META_ASSERT(num_tex_coords <= 4);   //  Generator limitation!
    UMP_META_ASSERT(is_valid);

    typedef typename Config::Pos                                    Pos;
    typedef typename Config::RHW                                    RHW;
    typedef typename Config::template Weights_Gen<num_weights>::Res Weights;
    typedef typename Config::Normal                                 Normal;
    typedef typename Config::Diffuse                                Diffuse;
    typedef typename Config::Specular                               Specular;
    typedef typename Config::template Tex_1_Gen<dim_tex_1>::Res     Tex_1;
    typedef typename Config::template Tex_2_Gen<dim_tex_2>::Res     Tex_2;
    typedef typename Config::template Tex_3_Gen<dim_tex_3>::Res     Tex_3;
    typedef typename Config::template Tex_4_Gen<dim_tex_4>::Res     Tex_4;

    UMP_META_ASSERT(sizeof(Pos)     == sizeof(float) * 3);
    UMP_META_ASSERT(sizeof(RHW)     == sizeof(float));
    UMP_META_ASSERT(sizeof(Weights) == sizeof(float) * num_weights);
    UMP_META_ASSERT(sizeof(Normal)  == sizeof(float) * 3);
    UMP_META_ASSERT(sizeof(Diffuse) == sizeof(float));
    UMP_META_ASSERT(sizeof(Specular)== sizeof(float));
    UMP_META_ASSERT(sizeof(Tex_1)   == sizeof(float) * dim_tex_1);
    UMP_META_ASSERT(sizeof(Tex_2)   == sizeof(float) * dim_tex_2);
    UMP_META_ASSERT(sizeof(Tex_3)   == sizeof(float) * dim_tex_3);
    UMP_META_ASSERT(sizeof(Tex_4)   == sizeof(float) * dim_tex_4);

    typedef typename Cat_If<has_pos,            void,   Pos     >::Res V_1;
    typedef typename Cat_If<has_rhw,            V_1,    RHW     >::Res V_2;
    typedef typename Cat_If<has_weights,        V_2,    Weights >::Res V_3;
    typedef typename Cat_If<has_normal,         V_3,    Normal  >::Res V_4;
    typedef typename Cat_If<has_diffuse,        V_4,    Diffuse >::Res V_5;
    typedef typename Cat_If<has_specular,       V_5,    Specular>::Res V_6;
    typedef typename Cat_If<(num_tex_coords>0), V_6,    Tex_1   >::Res V_7;
    typedef typename Cat_If<(num_tex_coords>1), V_7,    Tex_2   >::Res V_8;
    typedef typename Cat_If<(num_tex_coords>2), V_8,    Tex_3   >::Res V_9;
    typedef typename Cat_If<(num_tex_coords>3), V_9,    Tex_4   >::Res V_10;

public:
    typedef V_10 Res;
};

#undef UMP_META_ASSERT
}//namespace D3D_Util

#endif