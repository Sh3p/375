/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg
/// \version A04

#include <sstream>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// Note: I included just a few representative / unusually tricky test cases here.  You should write the others, for every function declared in Vector3.hpp.

SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
	REQUIRE (0.0f == Approx (v.m_x));
	REQUIRE (0.0f == Approx (v.m_y));
	REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
	REQUIRE (5.3f == Approx (v.m_x));
	REQUIRE (5.3f == Approx (v.m_y));
	REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
	REQUIRE (3.4f == Approx (v.m_x));
	REQUIRE (9.1f == Approx (v.m_y));
	REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}


// ... lots of missing functions ...


SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
	// Source: typed "dot product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

SCENARIO ("Vector3 angle between.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the angle between these two vectors.") {
      float angle = v1.cross (v2);
      THEN ("The cross product should be the product of two real vectors in three dimensions.") {
	// Source: typed "cross product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

SCENARIO ("Vector3 cross product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the cross product of the vectors.") {
      Vector3 cross = v1.cross (v2);
      THEN ("The cross product should be the product of two real vectors in three dimensions.") {
	// Source: typed "cross product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	REQUIRE (24.2f == Approx (v3.m_x) && -8.47 == Approx (v3.m_y) && -2.42 == Approx (v3.m_z));
      }
    }
  }
}


// ... lots of missing functions ...


SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	REQUIRE (false == equal);
      }
    }
  }
}
