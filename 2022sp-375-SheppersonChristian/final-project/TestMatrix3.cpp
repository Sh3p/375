/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Sean Malloy
/// \version A05

#include <sstream>

#include "Matrix3.hpp"
#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO("Matrix3 Constructors", "[Matrix3][A05]") {
  GIVEN("Nothing at all.") {
    WHEN("I use the default Matrix3 constructor.") {
      Matrix3 a;
      THEN("rx, uy, bz are 1.0f while all other elements should be 0.0f") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I pass 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f " +
          "into the constructor with 9 parameters") {
      Matrix3 b(1.0f, 2.0f, 3.0f, 
                4.0f, 5.0f, -6.0f, 
                -7.0f, 8.1f, 9.9f);
      THEN("Right vector is (1.0f, 2.0f, 3.0f), up vector is (4.0f, 5.0f, 6.0f) and " +
            "back vector is 7.0f, 8.0f, 9.0f") {
        REQUIRE(b.getRight() == Vector3(1.0f, 2.0f, 3.0f));
        REQUIRE(b.getUp() == Vector3(4.0f, 5.0f, 6.0f));
        REQUIRE(b.getBack() == Vector3(7.0f, 8.0f, 9.0f));
      }
    }

    WHEN("I pass three Vector3's containing (1.0f, 2.0f, 3.0f), (4.0f, 5.0f, 6.0f), " +
          "(7.0f, 8.0f, 9.0f) into the constructor with 9 parameters") {
      Vector3 right(1.0f, 2.0f, 3.0f);
      Vector3 up(4.0f, 5.0f, 6.0f);
      Vector3 back(7.0f, 8.0, 9.0f);
      Matrix3 a(right, up, back);
      THEN("Right vector is (1.0f, 2.0f, 3.0f), up vector is (4.0f, 5.0f, 6.0f) and " +
            "back vector is 7.0f, 8.0f, 9.0f") {
        REQUIRE(a.getRight() == right);
        REQUIRE(a.getUp() == up);
        REQUIRE(a.getBack() == back);
      }
    }

    WHEN("I pass a right Vector3 (5.0f, 0.0f, 0.0f) and up Vector3 (0.0f, -2.0f, 0.0f) into " +
          "and no boolean into the constructor that takes two vectors and an optional " +
          "boolean for orthonormal") {
      Vector3 right(5.0f, 0.0f, 0.0f);
      Vector3 up(0.0f, -2.0f, 0.0f);
      Matrix3 a(right, up);
      // TODO change this description lol
      THEN("The right and up vectors are unchanged while the back vector is their cross product") {
        REQUIRE(a.getRight() == right);
        REQUIRE(a.getUp() == up);
        REQUIRE(a.getBack() == right.cross(up));
      }
    }

    WHEN("I pass a right Vector3 (5.0f, 0.0f, 0.0f) and up Vector3 (0.0f, -2.0f, 0.0f) into " +
          "and true into the constructor that takes two vectors and an optional " +
          "boolean for orthonormal") {
      Vector3 right(5.0f, 0.0f, 0.0f);
      Vector3 up(0.0f, -2.0f, 0.0f);
      Matrix3 a(right, up, true);
      right.normalize();
      up.normalize();
      // TODO change this description lol
      THEN("The right and up vectors are normalized while the back vector is their cross product") {
        REQUIRE(a.getRight() == right);
        REQUIRE(a.getUp() == up);
        REQUIRE(a.getBack() == right.cross(up));
      }
    }
  }
}

SCENARIO("Set to Identity", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 2.0f, 3.0f), up vector (4.0f, 5.0f, 6.0f), and " +
  "back vector (7.0f, 8.0f, 9.0f)") {
    Matrix3 a;
    WHEN("I call setToIdentity() on the given matrix") {
      a.setToIdentity();
      THEN("The given matrix becomes the identity matrix") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }  
  }
}

SCENARIO("Set to Zero", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 2.0f, 3.0f), up vector (4.0f, 5.0f, 9.0f), and " +
  "back vector (7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I call setToZero() on the given matrix") {
      a.setToZero();
      THEN("Every element in the given matrix becomes 0") {
        REQUIRE(a.getRight() == Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 0.0f));
      }
    }  
  }
}

SCENARIO("Data pointer", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 2.0f, 3.0f), up vector (4.0f, 5.0f, 9.0f), and " +
  "back vector (7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I get the data pointer") {
      float* ptr = A.data();
      THEN("The data being pointed to should be 1.0f, the element in the first row and first column.") {
        REQUIRE(1.0f == Approx(*ptr));
      }
    }

    WHEN("I add 2 to the original data pointer.") {
      float* ptr = a.data();
      ptr += 2;
      THEN("The data being pointed to should be 7.0f, the element in the third row and first column.") {
        REQUIRE(7.0f == Approx(*ptr));
      }
    }

    WHEN("I add 3 to the original data pointer.") {
      float* ptr = a.data();
      ptr += 3;
      THEN("The data being pointed to should be 2.0f, the element in the first row and second column.") {
        REQUIRE(2.0f == Approx(*ptr));
      }
    }
  }
}

SCENARIO("Getters and setters", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 2.0f, 3.0f), up vector (4.0f, 5.0f, 9.0f), and " +
  "back vector (7.0f, 8.0f, 9.0f)") {
    Vector3 right(1.0f, 2.0f, 3.0f);
    Vector3 up(4.0f, 5.0f, 6.0f);
    Vector3 back(7.0f, 8.0f, 9.0f);
    Matrix3 a(right, up, back);

    WHEN("I call the getters for right, back, and up") {
      Vector3 matRight = a.getRight();
      Vector3 matUp = a.getUp();
      Vector3 matBack = a.getBack();
      THEN("Nothing has changed") {
        REQUIRE(matRight == right);
        REQUIRE(matUp == up);
        REQUIRE(matBack == back);
      }
    }

    WHEN("I set the right vector to be (-1.0f, -2.0f, -3.0f)") {
      Vector3 matUp = a.getUp();
      Vector3 matBack = a.getBack();
      Vector3 newRight(-1.0f, -2.0f, -3.0);
      a.setRight(newRight);
      THEN("Only the right vector has changed") {
        REQUIRE(newRight == a.getRight());
        REQUIRE(matUp == a.getUp());
        REQUIRE(matBack == a.getBack());
      }
    }

    WHEN("I set the up vector to be (-9.8f, 7.6f, 5.4f)") {
      Vector3 matRight = a.getRight();
      Vector3 matBack = a.getBack();
      Vector3 newUp(-9.8f, 7.6f, 5.4f);
      a.setUp(newUp);
      THEN("Only the up vector has changed") {
        REQUIRE(matRight == a.getRight());
        REQUIRE(newUp == a.getUp());
        REQUIRE(matBack == a.getBack());
      }
    }

    WHEN("I set the back vector to be (1.9f, 2.8f, -3.7f)") {
      Vector3 matRight = a.getRight();
      Vector3 matUp = a.getUp();
      Vector3 newBack(1.9f, 2.8f, -3.7f);
      a.setBack(newBack);
      THEN("Only the back vector has changed") {
        REQUIRE(matRight == a.getRight());
        REQUIRE(matUp == a.getUp());
        REQUIRE(newBack == a.getBack());
      }
    }

    WHEN("I set and get the forward vector") {
      Vector3 matRight = a.getRight();
      Vector3 matUp = a.getUp();
      Vector3 matForward(-1.9f, -2.8f, 3.7f);
      a.setForward(matForward);
      THEN("The back vector is equal to the negation of the forward vector. Right and up don't change") {
        REQUIRE(a.getForward() == -a.getBack());
        REQUIRE(matRight == a.getRight());
        REQUIRE(matUp == a.getUp());
      }
    }
  }
}

SCENARIO("Invert rotation matrix", "[Matrix3][A05]") {
  GIVEN("A rotation matrix, rotating counterclockwise by 90 degrees around the X-axis.") {
    Matrix3 rot(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    WHEN("I invert the matrix") {
      Matrix3 rotCopy = rot;
      rot.invertRotation();
      THEN("All non-diagonal values should flip signs") {
        float* oldData = rotCopy.data();
        float* newData = rot.data();
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            if (i != j)
              REQUIRE(*oldData == Approx(-(*newData)));
            ++oldData;
            ++newData;
          }
        }
      }
    }
  }
}

SCENARIO("Invert regular matrix", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (7.0f, 0.0f, -3.0f), up vector (2.0f, 3.0f, 4.0f), and " +
  "back vector (1.0f, -1.0f, -2.0f)") {
    Vector3 right(7.0f, 0.0f, -3.0f);
    Vector3 up(2.0f, 3.0f, 4.0f);
    Vector3 back(1.0f, -1.0f, -2.0f);
    Matrix3 a(right, up, back);
    WHEN("I invert the matrix") {
      a.invert();
      THEN("A matrix with right vector (-2.0f, 3.0f, 9.0f), up vector (8.0f, -11.0f, -34.0f), and " +
  "back vector (-5.0f, 7.0f, 21.0f)") {
        REQUIRE(a.getRight() == Vector3(-2.0f, 3.0f, 9.0f));
        REQUIRE(a.getUp() == Vector3(8.0f, -11.0f, -34.0f));
        REQUIRE(a.getBack() == Vector3(-5.0f, 7.0f, 21.0f));
      }
    }
  }
}

SCENARIO("Matrix Determinant", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (7.0f, 0.0f, -3.0f), up vector (2.0f, 3.0f, 4.0f), and " +
  "back vector (1.0f, -1.0f, -2.0f)") {
    Matrix3 a(-2.0f, 3.0f, 9.0f, 8.0f, -11.0f, -34.0f, -5.0f, 7.0f, 21.0f);
    WHEN("I find the determinant") {
      float det = a.determinant();
      THEN("The determinant is 81.0f") {
        REQUIRE(det == Approx(81.0f));
      }
    }
  }
}

SCENARIO("Orthonormalize", "[Matrix3][A05]") {
  GIVEN("A matrix with values (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I orthonormalize the matrix") {
      Matrix3 aCopy = a;
      a.orthonormalize();
      THEN("All columns have a length of 1") {
        REQUIRE(a.getRight().length() == Approx(1.0f));
        REQUIRE(a.getUp().length() == Approx(1.0f));
        REQUIRE(a.getBack().length() == Approx(1.0f));
      }
      THEN("All vectors are perpendicular to each other (dot product is 0)") {
        REQUIRE(a.getRight().dot(a.getBack()) == Approx(0.0f));
        REQUIRE(a.getRight().dot(a.getUp()) == Approx(0.0f));
        REQUIRE(a.getUp().dot(a.getBack()) == Approx(0.0f));
      }
      THEN("Back vector points in the same direction that it did before") {
        REQUIRE(a.getBack().dot(aCopy.getBack()) == 
          Approx(a.getBack().length() * aCopy.getBack().length()));
      }
    }
  }
}

SCENARIO("Set to scale", "[Matrix3][A05]") {
  GIVEN("A matrix with values (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I set the matrix to 2.0f * identity matrix") {
      a.setToScale(2.0f);
      THEN("All vectors are multiplied by scalar 2.0f") {
        REQUIRE(a.getRight() == Vector3(2.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 2.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 2.0f));
      }
    }

    WHEN("I scale x, y, and z by 2.0f, 0.5f, and -1.0f respectively") {
      a.setToScale(2.0f, 0.5f, -1.0f);
      THEN("The matrix becomes (2.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 3.0f)") {
        REQUIRE(a.getRight() == Vector3(2.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 0.5f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, -1.0f));
      }
    }
  }
}

SCENARIO("Set to Shear", "[Matrix3][A05]") {
  GIVEN("A matrix (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I shear X by Y = 2 and Z = 2") {
      a.setToShearXByYz(2.0f, 2.0f);
      THEN("a becomes (1.0f, 0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 2.0f, 0,.0f 1.0f)") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(2.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(2.0f, 0.0f, 1.0f));
      }
    }
    WHEN("I shear Y by X and Z") {
      a.setToShearYByXz(2.0f, 2.0f);
      THEN("a becomes (1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 1.0f)") {
        REQUIRE(a.getRight() == Vector3(1.0f, 2.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 2.0f, 1.0f));
      }
    }
    WHEN("I shear Z by X and Y") {
      a.setToShearZByXy(2.0f, 2.0f);
      THEN("a becomes (1.0f, 0.0f, 2.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f)") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 2.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 2.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Set to rotation", "[Matrix3][A05]") {
  GIVEN("a becomes (1.0f, 0.0f, 2.0f, 0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 1.0f)") {
    Matrix3 A(-9.0f, 5.0f, 6.2f, 1.0f, 7.0f, 3.0f, 8.0f, 2.0f, -10.1f);
    WHEN("I rotate around the X-axis by 90 degrees") {
      a.setToRotationX(90);
      THEN("The matrix becomes rotation matrix (1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f)") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 0.0f, 1.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, -1.0f, 0.0f));
      }
    }
    WHEN("I rotate around the Y-axis by 90 degrees") {
      a.setToRotationY(90);
      THEN("The matrix becomes rotation matrix (0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f)") {
        REQUIRE(a.getRight() == Vector3(0.0f, 0.0f, -1.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(1.0f, 0.0f, 0.0f));
      }
    }
    WHEN("I rotate around the Z-axis by 90 degrees") {
      a.setToRotationZ(90);
      THEN("The matrix becomes rotation matrix (0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)") {
        REQUIRE(a.getRight() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(-1.0f, 0.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Set from angle axis", "[Matrix3][A05]") {
  GIVEN("A matrix (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("Rotate around the vector (0.0f, 3.0f, 4.0f), by 30 degrees") {
      Vector3 rot(0.0f, 3.0f, 4.0f);
      a.setFromAngleAxis(30, rot);
      THEN("The matrix becomes arbitrary rotation matrix using a normalized " + 
        "rotation vector in the same direction") {
        REQUIRE(a.getRight() == Vector3(0.866025f, 0.4f, -0.3f));
        REQUIRE(a.getUp() == Vector3(-0.4f, 0.914256f, 0.064308f));
        REQUIRE(a.getBack() == Vector3(0.3f, 0.064308f, 0.951769f));
      }
    }
  }
}

SCENARIO("Negate", "[Matrix3][A05]") {
  GIVEN("A matrix (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I negate the matrix") {
      a.invertRotation();
      THEN("Matrix is transposed") {
        REQUIRE(a.getRight() == Vector3(1.0f, 4.0f, 7.0f));
        REQUIRE(a.getUp() == Vector3(2.0f, 5.0f, 8.0f));
        REQUIRE(a.getBack() == Vector3(3.0f, 6.0f, 9.0f));
      }
    }
  }
}

SCENARIO("Transform", "[Matrix3][A05]") {
  GIVEN("A matrix (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I transform the vector (1.0f, 2.0f, 3.0f)") {
      Vector3 t = a.transform(Vector3(1.0f , 2.0f, 3.0f));
      THEN("I get the vector (2.0f, 4.0f, 6.0f)") {
        REQUIRE(t == Vector3(2.0f, 4.0f, 6.0f));
      }
    }
  }
}

SCENARIO("Matrix addition", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f) and " +
  "(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f) respectively") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 b(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    WHEN("I use operator + to add first matrix by the second.") {
      Matrix3 c = a + b;
      THEN("The resulting matrix should be (10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f") {
        REQUIRE(c == Matrix3(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f));
      }
      
      THEN("a and b have not changed") {
        REQUIRE(a == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(b == Matrix3(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
      }
    }

    WHEN("I use operator += to add the first matrix by the second") {
      a += b;
      THEN("The resulting matrix should be (10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f)") {
        REQUIRE(a == Matrix3(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f));
      }
      
      THEN("b has not changed") {
        REQUIRE(b == Matrix3(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Matrix subtraction", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f) and " +
  "(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f) respectively") {
    Matrix3 c(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 b(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
    WHEN("I use operator - to subtract first matrix by the second.") {
      Matrix3 c = a - b;
      THEN("The resulting matrix should be (-8.0f, -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f, 8.0f)") {
        REQUIRE(c == Matrix3(-8.0f, -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f, 8.0f));
      }
      
      THEN("a and b have not changed") {
        REQUIRE(a == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(b == Matrix3(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
      }
    }

    WHEN("I use operator -= to subtract the first matrix by the second") {
      a -= b;
      THEN("The resulting matrix should be (-8.0f, -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f, 8.0f)") {
        REQUIRE(a == Matrix3(-8.0f, -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f, 8.0f));
      }
      
      THEN("b has not changed") {
        REQUIRE(b == Matrix3(9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Matrix-scalar multiplication", "[Matrix3][A05]") {
  GIVEN("An identity matrix") {
    Matrix3 a;
    a.setToIdentity();
    WHEN("I multiply the identity matrix by scalar 3") {
      Matrix3 b = a * 5;
      THEN("The matrix becomes (3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f)") {
        REQUIRE(b.getRight() == Vector3(3.0f, 0.0f, 0.0f));
        REQUIRE(b.getUp() == Vector3(0.0f, 3.0f, 0.0f));
        REQUIRE(b.getBack() == Vector3(0.0f, 0.0f, 3.0f));
      }
      THEN("The given matrix does not change") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I multiply the identity matrix by scalar 3") {
      Matrix3 b = 3 * a;
      THEN("The result is (3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f)") {
        REQUIRE(b.getRight() == Vector3(3.0f, 0.0f, 0.0f));
        REQUIRE(b.getUp() == Vector3(0.0f, 3.0f, 0.0f));
        REQUIRE(b.getBack() == Vector3(0.0f, 0.0f, 3.0f));
      }
      THEN("The given matrix does not change") {
        REQUIRE(a.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I set the identity matrix equal to itself multiplied by scalar 3") {
      a *= 3;
      THEN("The matrix becomes (3.0f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 3.0f)") {
        REQUIRE(a.getRight() == Vector3(3.0f, 0.0f, 0.0f));
        REQUIRE(a.getUp() == Vector3(0.0f, 3.0f, 0.0f));
        REQUIRE(a.getBack() == Vector3(0.0f, 0.0f, 3.0f));
      }
    }
  }
}

SCENARIO("Matrix-matrix multiplication", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) and " +
  "(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f) respectively") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 b(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f);
    WHEN("I use operator * to multiply first matrix by the second.") {
      Matrix3 c = a * b;
      THEN("The resulting matrix should be (54, 72, 84, 4, 11, 18, -63, -85, -96)") {
        REQUIRE(c == Matrix3(60.0f, 72.0f, 84.0f, 4.0f, 11.0f, 18.0f, -74.0f, -85.0f, -96.0f));
      }
      
      THEN("a and b have not changed") {
        REQUIRE(a == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(b == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }

    WHEN("I use operator *= to multiply the first matrix by the second") {
      a *= b;
      THEN("The resulting matrix should be (54.0f, 72.0f, 84.0f, 4.0f, 11.0f, 18.0f, -63.0f, -85.0f, -96.0f)") {
        REQUIRE(a == Matrix3(60.0f, 72.0f, 84.0f, 4.0f, 11.0f, 18.0f, -74.0f, -85.0f, -96.0f));
      }
      
      THEN("b has not changed") {
        REQUIRE(b == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }
  }
}

SCENARIO("Matrix-vector multiplication", "[Matrix3][A05]") {
  GIVEN("A matrix initialized to (0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f)") {
    Matrix3 a(-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    WHEN("I multiply the matrix by the vector (1.0f, 2.0f, 3.0f)") {
      Vector3 t = a.transform(Vector3(1.0f , 2.0f, 3.0f));
      THEN("I get the vector (1.0f, 3.0f, 3.0f)") {
        REQUIRE(t == Vector3(1.0f, 3.0f, 3.0f));
      }
    }
  }
}

SCENARIO ("Matrix3 stream insertion.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << a;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
        std::string line1 = "      1.00      2.00      3.00\n";
        std::string line2 = "      4.00      5.00      6.00\n";
        std::string line3 = "      7.00      8.00      9.00\n";
        std::string outTest = line1 + line2 + line3;
	      REQUIRE (outTest == out.str());
      }
      THEN ("The original stream should have been returned.") {
	      REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Matrix3 equality.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
    Matrix3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN ("I compare with a matrix initialized with (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)") {
      Matrix3 b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
      bool equal = a == b;
      THEN ("They should be equal.") {
	      REQUIRE (true == equal);
      }
    }

    WHEN ("I compare with a vector initialized with (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f)") {
      Matrix3 c(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f);
      bool equal = a == c;
      THEN ("They should not be equal.") {
	      REQUIRE (false == equal);
      }
    }
  }
}