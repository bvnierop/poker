#include "catch.hpp"

// RSPEC-style
#ifdef CATCH_CONFIG_VARIADIC_MACROS
#define Describe( ... ) TEST_CASE( "Describe " __VA_ARGS__ )
#define DescribeMethod( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Describe " __VA_ARGS__ )
#else
#define Describe( name, tags ) TEST_CASE( "Describe " name, tags )
#define DescribeMethod( className, name, tags ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Describe " name, tags )
#endif
#define Context( desc )    SECTION( std::string("  Context: ") + desc, "" )
#define It( desc )         SECTION( std::string("       It ") + desc, "" )

// "BDD-style" convenience wrappers
#ifdef CATCH_CONFIG_VARIADIC_MACROS
#define CatchDescribe( ... ) CATCH_TEST_CASE( "Describe " __VA_ARGS__ )
#define CatchDescribe_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Describe " __VA_ARGS__ )
#else
#define CatchDescribe( name, tags ) CATCH_TEST_CASE( "Describe " name, tags )
#define CatchDescribe_METHOD( className, name, tags ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Describe " name, tags )
#endif
#define CatchContext( desc )    CATCH_SECTION( std::string( "Context: ") + desc, "" )
#define CatchIt( desc )         CATCH_SECTION( std::string( "     It ") + desc, "" )


#define Expect( expr ) INTERNAL_CATCH_TEST( expr, Catch::ResultDisposition::Normal, "Expect" )
#define ExpectFalse( expr ) INTERNAL_CATCH_TEST( expr, Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, "ExpectFalse" )

#define ExpectThrows( expr ) INTERNAL_CATCH_THROWS( expr, Catch::ResultDisposition::Normal, "", "ExpectThrows" )
#define ExpectThrowsAs( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( expr, exceptionType, Catch::ResultDisposition::Normal, "ExpectThrowsAs" )
#define ExpectThrowsWith( expr, matcher ) INTERNAL_CATCH_THROWS( expr, Catch::ResultDisposition::Normal, matcher, "ExpectThrowsWith" )
#define ExpectNoThrow( expr ) INTERNAL_CATCH_NO_THROW( expr, Catch::ResultDisposition::Normal, "ExpectNoThrow" )
#define ExpectThat( arg, matcher ) INTERNAL_CHECK_THAT( arg, matcher, Catch::ResultDisposition::Normal, "ExpectThat" )

/* #define CHECK( expr ) INTERNAL_CATCH_TEST( expr, Catch::ResultDisposition::ContinueOnFailure, "CHECK" ) */
/* #define CHECK_FALSE( expr ) INTERNAL_CATCH_TEST( expr, Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, "CHECK_FALSE" ) */
/* #define CHECKED_IF( expr ) INTERNAL_CATCH_IF( expr, Catch::ResultDisposition::ContinueOnFailure, "CHECKED_IF" ) */
/* #define CHECKED_ELSE( expr ) INTERNAL_CATCH_ELSE( expr, Catch::ResultDisposition::ContinueOnFailure, "CHECKED_ELSE" ) */
/* #define CHECK_NOFAIL( expr ) INTERNAL_CATCH_TEST( expr, Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, "CHECK_NOFAIL" ) */

/* #define CHECK_THROWS( expr )  INTERNAL_CATCH_THROWS( expr, Catch::ResultDisposition::ContinueOnFailure, "", "CHECK_THROWS" ) */
/* #define CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( expr, exceptionType, Catch::ResultDisposition::ContinueOnFailure, "CHECK_THROWS_AS" ) */
/* #define CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS( expr, Catch::ResultDisposition::ContinueOnFailure, matcher, "CHECK_THROWS_WITH" ) */
/* #define CHECK_NOTHROW( expr ) INTERNAL_CATCH_NO_THROW( expr, Catch::ResultDisposition::ContinueOnFailure, "CHECK_NOTHROW" ) */

/* #define CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( arg, matcher, Catch::ResultDisposition::ContinueOnFailure, "CHECK_THAT" ) */
