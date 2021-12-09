/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "miniC.y"

//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
    #include "asm.h"
    #include <fstream>
    #include <iostream>

    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
    #define YYDEBUG 1
    #define EQUAL 1
    #define PLUSEQUAL 2
    #define MINUSEQUAL 3

    Asm assemblyFile;

    void writeFile(string name){
        ofstream file;
        file.open(name);
        file << assemblyFile.data << endl
        << assemblyFile.global <<endl
        << assemblyFile.text << endl;
        file.close();
    }

#line 103 "miniC_parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tokens.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_LIT_STRING = 3,              /* TK_LIT_STRING  */
  YYSYMBOL_TK_ID = 4,                      /* TK_ID  */
  YYSYMBOL_TK_LIT_INT = 5,                 /* TK_LIT_INT  */
  YYSYMBOL_TK_LIT_FLOAT = 6,               /* TK_LIT_FLOAT  */
  YYSYMBOL_TK_IF = 7,                      /* TK_IF  */
  YYSYMBOL_TK_ELSE = 8,                    /* TK_ELSE  */
  YYSYMBOL_TK_WHILE = 9,                   /* TK_WHILE  */
  YYSYMBOL_TK_RETURN = 10,                 /* TK_RETURN  */
  YYSYMBOL_TK_VOID = 11,                   /* TK_VOID  */
  YYSYMBOL_TK_INT_TYPE = 12,               /* TK_INT_TYPE  */
  YYSYMBOL_TK_FLOAT_TYPE = 13,             /* TK_FLOAT_TYPE  */
  YYSYMBOL_TK_PRINTF = 14,                 /* TK_PRINTF  */
  YYSYMBOL_TK_PLUS_EQUAL = 15,             /* TK_PLUS_EQUAL  */
  YYSYMBOL_TK_MINUS_EQUAL = 16,            /* TK_MINUS_EQUAL  */
  YYSYMBOL_TK_PLUS_PLUS = 17,              /* TK_PLUS_PLUS  */
  YYSYMBOL_TK_MINUS_MINUS = 18,            /* TK_MINUS_MINUS  */
  YYSYMBOL_TK_NOT = 19,                    /* TK_NOT  */
  YYSYMBOL_TK_OR = 20,                     /* TK_OR  */
  YYSYMBOL_TK_AND = 21,                    /* TK_AND  */
  YYSYMBOL_TK_EQUAL = 22,                  /* TK_EQUAL  */
  YYSYMBOL_TK_NOT_EQUAL = 23,              /* TK_NOT_EQUAL  */
  YYSYMBOL_TK_GREATER_OR_EQUAL = 24,       /* TK_GREATER_OR_EQUAL  */
  YYSYMBOL_TK_LESS_OR_EQUAL = 25,          /* TK_LESS_OR_EQUAL  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* ';'  */
  YYSYMBOL_29_ = 29,                       /* ','  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '['  */
  YYSYMBOL_32_ = 32,                       /* ']'  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '<'  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_start = 42,                     /* start  */
  YYSYMBOL_input = 43,                     /* input  */
  YYSYMBOL_external_declaration = 44,      /* external_declaration  */
  YYSYMBOL_method_definition = 45,         /* method_definition  */
  YYSYMBOL_declaration_list = 46,          /* declaration_list  */
  YYSYMBOL_declaration = 47,               /* declaration  */
  YYSYMBOL_init_declarator_list = 48,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 49,           /* init_declarator  */
  YYSYMBOL_declarator = 50,                /* declarator  */
  YYSYMBOL_parameters_type_list = 51,      /* parameters_type_list  */
  YYSYMBOL_parameter_declaration = 52,     /* parameter_declaration  */
  YYSYMBOL_initializer = 53,               /* initializer  */
  YYSYMBOL_initializer_list = 54,          /* initializer_list  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_statement_list = 56,            /* statement_list  */
  YYSYMBOL_if_statement = 57,              /* if_statement  */
  YYSYMBOL_expression_statement = 58,      /* expression_statement  */
  YYSYMBOL_while_statement = 59,           /* while_statement  */
  YYSYMBOL_jump_statement = 60,            /* jump_statement  */
  YYSYMBOL_block_statement = 61,           /* block_statement  */
  YYSYMBOL_type = 62,                      /* type  */
  YYSYMBOL_primary_expression = 63,        /* primary_expression  */
  YYSYMBOL_assignment_expression = 64,     /* assignment_expression  */
  YYSYMBOL_postfix_expression = 65,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 66,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 67,          /* unary_expression  */
  YYSYMBOL_multiplicative_expression = 68, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 69,       /* additive_expression  */
  YYSYMBOL_relational_expression = 70,     /* relational_expression  */
  YYSYMBOL_equality_expression = 71,       /* equality_expression  */
  YYSYMBOL_logical_or_expression = 72,     /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 73,    /* logical_and_expression  */
  YYSYMBOL_assignment_operator = 74,       /* assignment_operator  */
  YYSYMBOL_expression = 75,                /* expression  */
  YYSYMBOL_constant = 76                   /* constant  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,    35,    37,    29,    38,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
      40,    30,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    86,    86,   101,   102,   105,   106,   109,   113,   118,
     121,   128,   129,   132,   135,   136,   139,   140,   143,   144,
     145,   148,   149,   152,   153,   154,   157,   162,   165,   166,
     169,   170,   171,   172,   173,   174,   177,   178,   181,   182,
     185,   188,   191,   194,   199,   200,   210,   211,   212,   215,
     216,   217,   218,   221,   230,   233,   234,   235,   236,   237,
     238,   242,   243,   246,   247,   248,   249,   252,   253,   254,
     257,   258,   259,   262,   263,   264,   265,   266,   269,   270,
     271,   274,   275,   278,   279,   282,   283,   284,   287,   290,
     291
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TK_LIT_STRING",
  "TK_ID", "TK_LIT_INT", "TK_LIT_FLOAT", "TK_IF", "TK_ELSE", "TK_WHILE",
  "TK_RETURN", "TK_VOID", "TK_INT_TYPE", "TK_FLOAT_TYPE", "TK_PRINTF",
  "TK_PLUS_EQUAL", "TK_MINUS_EQUAL", "TK_PLUS_PLUS", "TK_MINUS_MINUS",
  "TK_NOT", "TK_OR", "TK_AND", "TK_EQUAL", "TK_NOT_EQUAL",
  "TK_GREATER_OR_EQUAL", "TK_LESS_OR_EQUAL", "'('", "')'", "';'", "','",
  "'='", "'['", "']'", "'{'", "'}'", "'*'", "'/'", "'+'", "'-'", "'>'",
  "'<'", "$accept", "start", "input", "external_declaration",
  "method_definition", "declaration_list", "declaration",
  "init_declarator_list", "init_declarator", "declarator",
  "parameters_type_list", "parameter_declaration", "initializer",
  "initializer_list", "statement", "statement_list", "if_statement",
  "expression_statement", "while_statement", "jump_statement",
  "block_statement", "type", "primary_expression", "assignment_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_or_expression",
  "logical_and_expression", "assignment_operator", "expression",
  "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-64)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     169,   -64,   -64,   -64,     7,   169,   -64,   -64,   -64,     6,
     -64,   -64,   -22,   -12,   -64,   -18,    58,   187,   -64,    19,
     170,    20,    13,   -64,     4,   -64,   -64,   -64,   -64,   221,
     221,   221,   221,   -64,   -64,    18,   211,    98,    64,    74,
      56,    93,    72,    63,   -64,    66,   -64,   221,   -64,   -64,
      15,    76,    10,   169,    75,   -64,   -64,   -64,   -64,   -64,
      82,   -64,   -64,   -64,   204,   221,   -64,   -64,   -64,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,    17,   -64,    72,    99,   111,   221,   221,   -64,
     135,   -64,   -64,    84,   -64,   -64,   -64,   -64,   -64,    19,
     127,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,    50,
     132,   -64,   -64,   -64,    64,    64,    74,    74,    74,    74,
      56,    56,    63,    93,   221,   -64,   221,   221,   137,   138,
     -64,   117,   -64,   -64,   -64,   -64,   221,   -64,    72,   142,
     150,   -64,   -64,   -64,   -64,   153,   153,   175,   -64,   153,
     -64
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    46,    47,    48,     0,     2,     4,     5,     6,     0,
       1,     3,    18,     0,    15,    16,     0,     0,    13,     0,
       0,     0,     0,    22,    24,    52,    50,    89,    90,     0,
       0,     0,     0,    20,    55,     0,    66,    69,    72,    77,
      80,    84,    54,    82,    51,    18,    14,     0,    17,    26,
       0,     8,     0,     0,     0,    23,    63,    64,    65,    88,
       0,    19,    59,    60,     0,     0,    86,    87,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,    29,     0,     0,     0,     0,    45,
       0,    12,    37,     0,    32,    31,    30,    34,    33,     0,
       0,    10,     9,     7,    21,    25,    49,    57,    62,     0,
       0,    53,    67,    68,    70,    71,    75,    76,    73,    74,
      78,    79,    81,    83,     0,    27,     0,     0,     0,     0,
      11,     0,    43,    36,    40,    58,     0,    56,    28,     0,
       0,    42,    35,    44,    61,     0,     0,    38,    41,     0,
      39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -64,   -64,   -64,   173,   -64,   -64,   -45,   -64,   165,   161,
     -64,   141,   -64,   -64,   -63,   105,   -64,   -64,   -64,   -64,
     -15,   -14,   -64,   -17,   -64,   -64,   -16,    57,    -2,    54,
     116,   -46,   118,   -64,   -21,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,    90,     8,    13,    14,    15,
      22,    23,    48,    82,    92,    93,    94,    95,    96,    97,
      98,     9,    34,    59,    36,   109,    37,    38,    39,    40,
      41,    42,    43,    69,   100,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      35,    84,    24,    49,    16,    91,    51,    10,    45,    17,
      12,    60,    20,    56,    57,    58,    18,    19,    25,    26,
      27,    28,    85,    45,    86,    87,     1,     2,     3,    88,
     133,    83,    29,    30,    31,    54,    99,   103,   102,    24,
      52,    32,    53,    50,   110,   130,   124,   108,    50,    89,
      61,   125,   111,    50,   112,   113,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,   128,   129,   133,     1,
       2,     3,   116,   117,   118,   119,    99,   135,   138,   136,
      74,    75,   147,   148,    81,    21,   150,    25,    26,    27,
      28,    85,    80,    86,    87,    76,    77,    17,    88,    70,
      71,    29,    30,    31,   101,   139,   140,   105,    83,   106,
      32,    72,    73,    66,    67,    78,    79,    50,   132,   144,
      25,    26,    27,    28,    85,   126,    86,    87,    68,   114,
     115,    88,   120,   121,    29,    30,    31,   127,    25,    26,
      27,    28,    85,    32,    86,    87,     1,     2,     3,    88,
      50,   143,    29,    30,    31,   134,    25,    26,    27,    28,
      85,    32,    86,    87,   137,   141,   142,    88,    50,   145,
      29,    30,    31,    25,    26,    27,    28,   146,    11,    32,
       1,     2,     3,   149,    46,    55,    50,    29,    30,    31,
      25,    26,    27,    28,   104,   131,    32,   123,   122,     0,
       0,     0,     0,    47,    29,    30,    31,    25,    26,    27,
      28,     0,     0,    32,     0,     0,     0,     0,     0,    33,
       0,    29,    30,    31,    25,    26,    27,    28,    62,    63,
      32,   107,     0,     0,     0,     0,     0,    64,    29,    30,
      31,     0,    65,     0,     0,     0,     0,    32
};

static const yytype_int16 yycheck[] =
{
      17,    47,    16,    20,    26,    50,    21,     0,     4,    31,
       4,    32,    30,    29,    30,    31,    28,    29,     3,     4,
       5,     6,     7,     4,     9,    10,    11,    12,    13,    14,
      93,    47,    17,    18,    19,    31,    50,    52,    28,    53,
      27,    26,    29,    33,    65,    90,    29,    64,    33,    34,
      32,    34,    69,    33,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    87,    88,   131,    11,
      12,    13,    74,    75,    76,    77,    90,    27,   124,    29,
      24,    25,   145,   146,    21,    27,   149,     3,     4,     5,
       6,     7,    20,     9,    10,    39,    40,    31,    14,    35,
      36,    17,    18,    19,    28,   126,   127,    32,   124,    27,
      26,    37,    38,    15,    16,    22,    23,    33,    34,   136,
       3,     4,     5,     6,     7,    26,     9,    10,    30,    72,
      73,    14,    78,    79,    17,    18,    19,    26,     3,     4,
       5,     6,     7,    26,     9,    10,    11,    12,    13,    14,
      33,    34,    17,    18,    19,    28,     3,     4,     5,     6,
       7,    26,     9,    10,    32,    28,    28,    14,    33,    27,
      17,    18,    19,     3,     4,     5,     6,    27,     5,    26,
      11,    12,    13,     8,    19,    24,    33,    17,    18,    19,
       3,     4,     5,     6,    53,    90,    26,    81,    80,    -1,
      -1,    -1,    -1,    33,    17,    18,    19,     3,     4,     5,
       6,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    17,    18,    19,     3,     4,     5,     6,    17,    18,
      26,    27,    -1,    -1,    -1,    -1,    -1,    26,    17,    18,
      19,    -1,    31,    -1,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,    12,    13,    42,    43,    44,    45,    47,    62,
       0,    44,     4,    48,    49,    50,    26,    31,    28,    29,
      30,    27,    51,    52,    62,     3,     4,     5,     6,    17,
      18,    19,    26,    32,    63,    64,    65,    67,    68,    69,
      70,    71,    72,    73,    76,     4,    49,    33,    53,    64,
      33,    61,    27,    29,    31,    50,    67,    67,    67,    64,
      75,    32,    17,    18,    26,    31,    15,    16,    30,    74,
      35,    36,    37,    38,    24,    25,    39,    40,    22,    23,
      20,    21,    54,    67,    72,     7,     9,    10,    14,    34,
      46,    47,    55,    56,    57,    58,    59,    60,    61,    62,
      75,    28,    28,    61,    52,    32,    27,    27,    64,    66,
      75,    64,    67,    67,    68,    68,    69,    69,    69,    69,
      70,    70,    73,    71,    29,    34,    26,    26,    75,    75,
      47,    56,    34,    55,    28,    27,    29,    32,    72,    75,
      75,    28,    28,    34,    64,    27,    27,    55,    55,     8,
      55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    45,
      45,    46,    46,    47,    48,    48,    49,    49,    50,    50,
      50,    51,    51,    52,    52,    52,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    56,    56,    57,    57,
      58,    59,    60,    61,    61,    61,    62,    62,    62,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    67,    67,    68,    68,    68,
      69,    69,    69,    70,    70,    70,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    74,    74,    74,    75,    76,
      76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     6,     5,     6,
       6,     2,     1,     3,     3,     1,     1,     3,     1,     4,
       3,     3,     1,     2,     1,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     5,     7,
       2,     5,     3,     3,     4,     2,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     4,     3,     4,     2,
       2,     3,     1,     2,     2,     2,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: input  */
#line 86 "miniC.y"
            {
    assemblyFile.global = ".globl main";
    assemblyFile.data = ".data\n";
    assemblyFile.text = ".text\n";
    list<Statement *>::iterator it = (yyvsp[0].statement_list_t)->begin();
    string code;
    while(it != (yyvsp[0].statement_list_t)->end()){
        printf("semantic result: %d \n",(*it)->evaluateSemantic());
        code += (*it)->genCode();
        it++;
    }
    assemblyFile.text += code;
    writeFile("result.s");
}
#line 1311 "miniC_parser.cpp"
    break;

  case 3: /* input: input external_declaration  */
#line 101 "miniC.y"
                                  {(yyval.statement_list_t) = (yyvsp[-1].statement_list_t); (yyval.statement_list_t)->push_back((yyvsp[0].statement_t));}
#line 1317 "miniC_parser.cpp"
    break;

  case 4: /* input: external_declaration  */
#line 102 "miniC.y"
                           {(yyval.statement_list_t) = new StatementList; (yyval.statement_list_t)->push_back((yyvsp[0].statement_t));}
#line 1323 "miniC_parser.cpp"
    break;

  case 5: /* external_declaration: method_definition  */
#line 105 "miniC.y"
                                        {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1329 "miniC_parser.cpp"
    break;

  case 6: /* external_declaration: declaration  */
#line 106 "miniC.y"
                          {(yyval.statement_t) = new GlobalDeclaration((yyvsp[0].declaration_t));}
#line 1335 "miniC_parser.cpp"
    break;

  case 7: /* method_definition: type TK_ID '(' parameters_type_list ')' block_statement  */
#line 109 "miniC.y"
                                                                           {
                    (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-5].int_t), (yyvsp[-4].string_t), *(yyvsp[-2].parameter_list_t), (yyvsp[0].statement_t), yylineno );
                    delete (yyvsp[-2].parameter_list_t);
                 }
#line 1344 "miniC_parser.cpp"
    break;

  case 8: /* method_definition: type TK_ID '(' ')' block_statement  */
#line 113 "miniC.y"
                                                     {
                     ParameterList * pm = new ParameterList;
                     (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-4].int_t), (yyvsp[-3].string_t), *pm, (yyvsp[0].statement_t), yylineno );
                     delete pm;
                 }
#line 1354 "miniC_parser.cpp"
    break;

  case 9: /* method_definition: type TK_ID '(' parameters_type_list ')' ';'  */
#line 118 "miniC.y"
                                                              {
                     (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-5].int_t), (yyvsp[-4].string_t), *(yyvsp[-2].parameter_list_t), NULL, yylineno);
                 }
#line 1362 "miniC_parser.cpp"
    break;

  case 10: /* method_definition: type TK_ID '(' ')' block_statement ';'  */
#line 121 "miniC.y"
                                                         {
                     ParameterList * pm = new ParameterList;
                     (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-5].int_t), (yyvsp[-4].string_t), *pm , NULL, yylineno);
                     delete pm;
                 }
#line 1372 "miniC_parser.cpp"
    break;

  case 11: /* declaration_list: declaration_list declaration  */
#line 128 "miniC.y"
                                               { (yyval.declaration_list_t) = (yyvsp[-1].declaration_list_t); (yyval.declaration_list_t)->push_back((yyvsp[0].declaration_t)); }
#line 1378 "miniC_parser.cpp"
    break;

  case 12: /* declaration_list: declaration  */
#line 129 "miniC.y"
                              {(yyval.declaration_list_t) = new DeclarationList; (yyval.declaration_list_t)->push_back((yyvsp[0].declaration_t));}
#line 1384 "miniC_parser.cpp"
    break;

  case 13: /* declaration: type init_declarator_list ';'  */
#line 132 "miniC.y"
                                           { (yyval.declaration_t) = new Declaration((Type)(yyvsp[-2].int_t), *(yyvsp[-1].init_declarator_list_t), yylineno); delete (yyvsp[-1].init_declarator_list_t);  }
#line 1390 "miniC_parser.cpp"
    break;

  case 14: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 135 "miniC.y"
                                                               { (yyval.init_declarator_list_t) = (yyvsp[-2].init_declarator_list_t); (yyval.init_declarator_list_t)->push_back((yyvsp[0].init_declarator_t)); }
#line 1396 "miniC_parser.cpp"
    break;

  case 15: /* init_declarator_list: init_declarator  */
#line 136 "miniC.y"
                                  { (yyval.init_declarator_list_t) = new InitDeclaratorList; (yyval.init_declarator_list_t)->push_back((yyvsp[0].init_declarator_t)); }
#line 1402 "miniC_parser.cpp"
    break;

  case 16: /* init_declarator: declarator  */
#line 139 "miniC.y"
                            {(yyval.init_declarator_t) = new InitDeclarator((yyvsp[0].declarator_t), NULL, yylineno);}
#line 1408 "miniC_parser.cpp"
    break;

  case 17: /* init_declarator: declarator '=' initializer  */
#line 140 "miniC.y"
                                             { (yyval.init_declarator_t) = new InitDeclarator((yyvsp[-2].declarator_t), (yyvsp[0].initializer_t), yylineno); }
#line 1414 "miniC_parser.cpp"
    break;

  case 18: /* declarator: TK_ID  */
#line 143 "miniC.y"
                  {(yyval.declarator_t) = new Declarator((yyvsp[0].string_t), NULL, false, yylineno);}
#line 1420 "miniC_parser.cpp"
    break;

  case 19: /* declarator: TK_ID '[' assignment_expression ']'  */
#line 144 "miniC.y"
                                                { (yyval.declarator_t) = new Declarator((yyvsp[-3].string_t), (yyvsp[-1].expr_t), true, yylineno);}
#line 1426 "miniC_parser.cpp"
    break;

  case 20: /* declarator: TK_ID '[' ']'  */
#line 145 "miniC.y"
                          {(yyval.declarator_t) = new Declarator((yyvsp[-2].string_t), NULL, true, yylineno);}
#line 1432 "miniC_parser.cpp"
    break;

  case 21: /* parameters_type_list: parameters_type_list ',' parameter_declaration  */
#line 148 "miniC.y"
                                                                     {(yyval.parameter_list_t) = (yyvsp[-2].parameter_list_t); (yyval.parameter_list_t)->push_back((yyvsp[0].parameter_t));}
#line 1438 "miniC_parser.cpp"
    break;

  case 22: /* parameters_type_list: parameter_declaration  */
#line 149 "miniC.y"
                                           { (yyval.parameter_list_t) = new ParameterList; (yyval.parameter_list_t)->push_back((yyvsp[0].parameter_t)); }
#line 1444 "miniC_parser.cpp"
    break;

  case 23: /* parameter_declaration: type declarator  */
#line 152 "miniC.y"
                                       { (yyval.parameter_t) = new Parameter((Type)(yyvsp[-1].int_t), (yyvsp[0].declarator_t), false, yylineno); }
#line 1450 "miniC_parser.cpp"
    break;

  case 24: /* parameter_declaration: type  */
#line 153 "miniC.y"
                            { (yyval.parameter_t) = new Parameter((Type)(yyvsp[0].int_t), NULL, false, yylineno); }
#line 1456 "miniC_parser.cpp"
    break;

  case 25: /* parameter_declaration: type '[' ']'  */
#line 154 "miniC.y"
                                     { (yyval.parameter_t) = new Parameter((Type)(yyvsp[-2].int_t), NULL, true, yylineno); }
#line 1462 "miniC_parser.cpp"
    break;

  case 26: /* initializer: assignment_expression  */
#line 157 "miniC.y"
                                   {
    InitializerElementList * list = new InitializerElementList;
    list->push_back((yyvsp[0].expr_t));
    (yyval.initializer_t) = new Initializer(*list, yylineno);
}
#line 1472 "miniC_parser.cpp"
    break;

  case 27: /* initializer: '{' initializer_list '}'  */
#line 162 "miniC.y"
                                     { (yyval.initializer_t) = new Initializer(*(yyvsp[-1].initializer_list_t), yylineno); delete (yyvsp[-1].initializer_list_t);  }
#line 1478 "miniC_parser.cpp"
    break;

  case 28: /* initializer_list: initializer_list ',' logical_or_expression  */
#line 165 "miniC.y"
                                                             { (yyval.initializer_list_t) = (yyvsp[-2].initializer_list_t); (yyval.initializer_list_t)->push_back((yyvsp[0].expr_t)); }
#line 1484 "miniC_parser.cpp"
    break;

  case 29: /* initializer_list: logical_or_expression  */
#line 166 "miniC.y"
                                        {(yyval.initializer_list_t) = new InitializerElementList; (yyval.initializer_list_t)->push_back((yyvsp[0].expr_t));}
#line 1490 "miniC_parser.cpp"
    break;

  case 30: /* statement: while_statement  */
#line 169 "miniC.y"
                           {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1496 "miniC_parser.cpp"
    break;

  case 31: /* statement: expression_statement  */
#line 170 "miniC.y"
                               {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1502 "miniC_parser.cpp"
    break;

  case 32: /* statement: if_statement  */
#line 171 "miniC.y"
                       {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1508 "miniC_parser.cpp"
    break;

  case 33: /* statement: block_statement  */
#line 172 "miniC.y"
                          {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1514 "miniC_parser.cpp"
    break;

  case 34: /* statement: jump_statement  */
#line 173 "miniC.y"
                         {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1520 "miniC_parser.cpp"
    break;

  case 35: /* statement: TK_PRINTF expression ';'  */
#line 174 "miniC.y"
                                   {(yyval.statement_t) = new PrintStatement((yyvsp[-1].expr_t), yylineno);}
#line 1526 "miniC_parser.cpp"
    break;

  case 36: /* statement_list: statement_list statement  */
#line 177 "miniC.y"
                                         { (yyval.statement_list_t) = (yyvsp[-1].statement_list_t); (yyval.statement_list_t)->push_back((yyvsp[0].statement_t)); }
#line 1532 "miniC_parser.cpp"
    break;

  case 37: /* statement_list: statement  */
#line 178 "miniC.y"
                          { (yyval.statement_list_t) = new StatementList; (yyval.statement_list_t)->push_back((yyvsp[0].statement_t)); }
#line 1538 "miniC_parser.cpp"
    break;

  case 38: /* if_statement: TK_IF '(' expression ')' statement  */
#line 181 "miniC.y"
                                                 {(yyval.statement_t) = new IfStatement((yyvsp[-2].expr_t), (yyvsp[0].statement_t), yylineno);}
#line 1544 "miniC_parser.cpp"
    break;

  case 39: /* if_statement: TK_IF '(' expression ')' statement TK_ELSE statement  */
#line 182 "miniC.y"
                                                                   {(yyval.statement_t) = new ElseStatement((yyvsp[-4].expr_t), (yyvsp[-2].statement_t), (yyvsp[0].statement_t), yylineno);}
#line 1550 "miniC_parser.cpp"
    break;

  case 40: /* expression_statement: expression ';'  */
#line 185 "miniC.y"
                                     {(yyval.statement_t) = new ExprStatement((yyvsp[-1].expr_t), yylineno);}
#line 1556 "miniC_parser.cpp"
    break;

  case 41: /* while_statement: TK_WHILE '(' expression ')' statement  */
#line 188 "miniC.y"
                                                       { (yyval.statement_t) = new WhileStatement((yyvsp[-2].expr_t), (yyvsp[0].statement_t), yylineno);}
#line 1562 "miniC_parser.cpp"
    break;

  case 42: /* jump_statement: TK_RETURN expression ';'  */
#line 191 "miniC.y"
                                         {(yyval.statement_t) = new ReturnStatement((yyvsp[-1].expr_t), yylineno);}
#line 1568 "miniC_parser.cpp"
    break;

  case 43: /* block_statement: '{' statement_list '}'  */
#line 194 "miniC.y"
                                        { 
                    DeclarationList * list = new DeclarationList();
                    (yyval.statement_t) = new BlockStatement(*(yyvsp[-1].statement_list_t), *list, yylineno);
                    delete list;
               }
#line 1578 "miniC_parser.cpp"
    break;

  case 44: /* block_statement: '{' declaration_list statement_list '}'  */
#line 199 "miniC.y"
                                                          {(yyval.statement_t) = new BlockStatement(*(yyvsp[-1].statement_list_t), *(yyvsp[-2].declaration_list_t), yylineno); delete (yyvsp[-2].declaration_list_t); delete (yyvsp[-1].statement_list_t); }
#line 1584 "miniC_parser.cpp"
    break;

  case 45: /* block_statement: '{' '}'  */
#line 200 "miniC.y"
                         {
                   StatementList * stmts = new StatementList();
                   DeclarationList * decls = new DeclarationList();
                   (yyval.statement_t) = new BlockStatement(*stmts, *decls, yylineno);
                   delete stmts;
                   delete decls;

               }
#line 1597 "miniC_parser.cpp"
    break;

  case 46: /* type: TK_VOID  */
#line 210 "miniC.y"
              {(yyval.int_t) = VOID;}
#line 1603 "miniC_parser.cpp"
    break;

  case 47: /* type: TK_INT_TYPE  */
#line 211 "miniC.y"
                 {(yyval.int_t) = INT;}
#line 1609 "miniC_parser.cpp"
    break;

  case 48: /* type: TK_FLOAT_TYPE  */
#line 212 "miniC.y"
                   {(yyval.int_t) = FLOAT;}
#line 1615 "miniC_parser.cpp"
    break;

  case 49: /* primary_expression: '(' expression ')'  */
#line 215 "miniC.y"
                                       {(yyval.expr_t) = (yyvsp[-1].expr_t);}
#line 1621 "miniC_parser.cpp"
    break;

  case 50: /* primary_expression: TK_ID  */
#line 216 "miniC.y"
            {(yyval.expr_t) = new IdExpr((yyvsp[0].string_t), yylineno);}
#line 1627 "miniC_parser.cpp"
    break;

  case 51: /* primary_expression: constant  */
#line 217 "miniC.y"
               {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1633 "miniC_parser.cpp"
    break;

  case 52: /* primary_expression: TK_LIT_STRING  */
#line 218 "miniC.y"
                    { (yyval.expr_t) = new StringExpr((yyvsp[0].string_t), yylineno); }
#line 1639 "miniC_parser.cpp"
    break;

  case 53: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 221 "miniC.y"
                                                                                  {
        if((yyvsp[-1].int_t) == EQUAL){
            (yyval.expr_t) = new AssignExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t),yylineno);
        }else if((yyvsp[-1].int_t) == PLUSEQUAL){
            (yyval.expr_t) = new PlusAssignExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t),yylineno);
        }else if((yyvsp[-1].int_t) == MINUSEQUAL){
            (yyval.expr_t) = new MinusAssignExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t),yylineno);
        }
}
#line 1653 "miniC_parser.cpp"
    break;

  case 54: /* assignment_expression: logical_or_expression  */
#line 230 "miniC.y"
                                             { (yyval.expr_t) = (yyvsp[0].expr_t); }
#line 1659 "miniC_parser.cpp"
    break;

  case 55: /* postfix_expression: primary_expression  */
#line 233 "miniC.y"
                                       {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1665 "miniC_parser.cpp"
    break;

  case 56: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 234 "miniC.y"
                                                            { (yyval.expr_t) = new ArrayExpr((IdExpr*)(yyvsp[-3].expr_t), (yyvsp[-1].expr_t), yylineno); }
#line 1671 "miniC_parser.cpp"
    break;

  case 57: /* postfix_expression: postfix_expression '(' ')'  */
#line 235 "miniC.y"
                                                 { (yyval.expr_t) = new MethodInvocationExpr((IdExpr*)(yyvsp[-2].expr_t), *(new ArgumentList), yylineno); }
#line 1677 "miniC_parser.cpp"
    break;

  case 58: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 236 "miniC.y"
                                                                          { (yyval.expr_t) = new MethodInvocationExpr((IdExpr*)(yyvsp[-3].expr_t), *(yyvsp[-1].argument_list_t), yylineno); }
#line 1683 "miniC_parser.cpp"
    break;

  case 59: /* postfix_expression: postfix_expression TK_PLUS_PLUS  */
#line 237 "miniC.y"
                                                      { (yyval.expr_t) = new PostIncrementExpr((IdExpr*)(yyvsp[-1].expr_t), yylineno); }
#line 1689 "miniC_parser.cpp"
    break;

  case 60: /* postfix_expression: postfix_expression TK_MINUS_MINUS  */
#line 238 "miniC.y"
                                                        { (yyval.expr_t) = new PostDecrementExpr((IdExpr*)(yyvsp[-1].expr_t), yylineno); }
#line 1695 "miniC_parser.cpp"
    break;

  case 61: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 242 "miniC.y"
                                                                             {(yyval.argument_list_t) = (yyvsp[-2].argument_list_t);  (yyval.argument_list_t)->push_back((yyvsp[0].expr_t));}
#line 1701 "miniC_parser.cpp"
    break;

  case 62: /* argument_expression_list: assignment_expression  */
#line 243 "miniC.y"
                                                { (yyval.argument_list_t) = new ArgumentList; (yyval.argument_list_t)->push_back((yyvsp[0].expr_t));}
#line 1707 "miniC_parser.cpp"
    break;

  case 63: /* unary_expression: TK_PLUS_PLUS unary_expression  */
#line 246 "miniC.y"
                                                {(yyval.expr_t) = new UnaryExpr(INCREMENT, (yyvsp[0].expr_t), yylineno);}
#line 1713 "miniC_parser.cpp"
    break;

  case 64: /* unary_expression: TK_MINUS_MINUS unary_expression  */
#line 247 "miniC.y"
                                                  {(yyval.expr_t) = new UnaryExpr(DECREMENT, (yyvsp[0].expr_t), yylineno);}
#line 1719 "miniC_parser.cpp"
    break;

  case 65: /* unary_expression: TK_NOT unary_expression  */
#line 248 "miniC.y"
                                           {(yyval.expr_t) = new UnaryExpr(NOT, (yyvsp[0].expr_t), yylineno);}
#line 1725 "miniC_parser.cpp"
    break;

  case 66: /* unary_expression: postfix_expression  */
#line 249 "miniC.y"
                                     { (yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1731 "miniC_parser.cpp"
    break;

  case 67: /* multiplicative_expression: multiplicative_expression '*' unary_expression  */
#line 252 "miniC.y"
                                                                          { (yyval.expr_t) = new MulExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1737 "miniC_parser.cpp"
    break;

  case 68: /* multiplicative_expression: multiplicative_expression '/' unary_expression  */
#line 253 "miniC.y"
                                                       { (yyval.expr_t) = new DivExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1743 "miniC_parser.cpp"
    break;

  case 69: /* multiplicative_expression: unary_expression  */
#line 254 "miniC.y"
                         {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1749 "miniC_parser.cpp"
    break;

  case 70: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 257 "miniC.y"
                                                                       { (yyval.expr_t) = new AddExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1755 "miniC_parser.cpp"
    break;

  case 71: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 258 "miniC.y"
                                                                        { (yyval.expr_t) = new SubExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1761 "miniC_parser.cpp"
    break;

  case 72: /* additive_expression: multiplicative_expression  */
#line 259 "miniC.y"
                                                {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1767 "miniC_parser.cpp"
    break;

  case 73: /* relational_expression: relational_expression '>' additive_expression  */
#line 262 "miniC.y"
                                                                     { (yyval.expr_t) = new GtExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1773 "miniC_parser.cpp"
    break;

  case 74: /* relational_expression: relational_expression '<' additive_expression  */
#line 263 "miniC.y"
                                                                     { (yyval.expr_t) = new LtExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1779 "miniC_parser.cpp"
    break;

  case 75: /* relational_expression: relational_expression TK_GREATER_OR_EQUAL additive_expression  */
#line 264 "miniC.y"
                                                                                     { (yyval.expr_t) = new GteExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1785 "miniC_parser.cpp"
    break;

  case 76: /* relational_expression: relational_expression TK_LESS_OR_EQUAL additive_expression  */
#line 265 "miniC.y"
                                                                                  { (yyval.expr_t) = new LteExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1791 "miniC_parser.cpp"
    break;

  case 77: /* relational_expression: additive_expression  */
#line 266 "miniC.y"
                                           {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1797 "miniC_parser.cpp"
    break;

  case 78: /* equality_expression: equality_expression TK_EQUAL relational_expression  */
#line 269 "miniC.y"
                                                                         { (yyval.expr_t) = new EqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1803 "miniC_parser.cpp"
    break;

  case 79: /* equality_expression: equality_expression TK_NOT_EQUAL relational_expression  */
#line 270 "miniC.y"
                                                                            { (yyval.expr_t) = new NeqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1809 "miniC_parser.cpp"
    break;

  case 80: /* equality_expression: relational_expression  */
#line 271 "miniC.y"
                                           {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1815 "miniC_parser.cpp"
    break;

  case 81: /* logical_or_expression: logical_or_expression TK_OR logical_and_expression  */
#line 274 "miniC.y"
                                                                          { (yyval.expr_t) = new LogicalOrExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1821 "miniC_parser.cpp"
    break;

  case 82: /* logical_or_expression: logical_and_expression  */
#line 275 "miniC.y"
                                             {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1827 "miniC_parser.cpp"
    break;

  case 83: /* logical_and_expression: logical_and_expression TK_AND equality_expression  */
#line 278 "miniC.y"
                                                                          { (yyval.expr_t) = new LogicalAndExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 1833 "miniC_parser.cpp"
    break;

  case 84: /* logical_and_expression: equality_expression  */
#line 279 "miniC.y"
                                            {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1839 "miniC_parser.cpp"
    break;

  case 85: /* assignment_operator: '='  */
#line 282 "miniC.y"
                         { (yyval.int_t) = EQUAL; }
#line 1845 "miniC_parser.cpp"
    break;

  case 86: /* assignment_operator: TK_PLUS_EQUAL  */
#line 283 "miniC.y"
                                   {(yyval.int_t) = PLUSEQUAL; }
#line 1851 "miniC_parser.cpp"
    break;

  case 87: /* assignment_operator: TK_MINUS_EQUAL  */
#line 284 "miniC.y"
                                    { (yyval.int_t) = MINUSEQUAL; }
#line 1857 "miniC_parser.cpp"
    break;

  case 88: /* expression: assignment_expression  */
#line 287 "miniC.y"
                                  {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1863 "miniC_parser.cpp"
    break;

  case 89: /* constant: TK_LIT_INT  */
#line 290 "miniC.y"
                     { (yyval.expr_t) = new IntExpr((yyvsp[0].int_t) , yylineno);}
#line 1869 "miniC_parser.cpp"
    break;

  case 90: /* constant: TK_LIT_FLOAT  */
#line 291 "miniC.y"
                       { (yyval.expr_t) = new FloatExpr((yyvsp[0].float_t) , yylineno);}
#line 1875 "miniC_parser.cpp"
    break;


#line 1879 "miniC_parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 293 "miniC.y"
