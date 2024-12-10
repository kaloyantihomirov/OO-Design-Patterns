#include <sstream>
#include "catch_amalgamated.hpp"

#include "CircleCreator.h"
#include "RandomFigureFactory.h"
#include "TriangleCreator.h"

struct RandomFigureFactoryTestFixture
{
    RandomFigureFactory factory;

    RandomFigureFactoryTestFixture()
    {
        factory.clearCreators();
    }

    void addDefaultCreators()
    {
        factory.registerFigure("triangle", std::make_unique<TriangleCreator>());
        factory.registerFigure("circle", std::make_unique<CircleCreator>());
    }
};

TEST_CASE_METHOD(RandomFigureFactoryTestFixture, 
    "RandomFigureFactory throws exception when no creators are registered")
{
    REQUIRE_THROWS(factory.createFigure());
}

TEST_CASE_METHOD(RandomFigureFactoryTestFixture, "RandomFigureFactory correctly creates figures without throwing exceptions when properly set up")
{
    addDefaultCreators();

    const size_t figuresCount = 1000;
    for (size_t i = 0; i < figuresCount; i++)
    {
        std::unique_ptr<Figure> figure;
        REQUIRE_NOTHROW(figure = factory.createFigure());
        REQUIRE(figure != nullptr);
    }
}

TEST_CASE_METHOD(RandomFigureFactoryTestFixture, "RandomFigureFactory creates valid figures without exceptions when allowed 2 figure types")
{
    addDefaultCreators();

    const size_t figuresCount = 1000;

    for (size_t i = 0; i < figuresCount; i++) 
    {
        std::unique_ptr<Figure> figure;
        REQUIRE_NOTHROW(figure = factory.createFigure());
        REQUIRE(figure != nullptr);

        std::string type = figure->toString().substr(0, figure->toString().find(' '));
        REQUIRE((type == "triangle" || type == "circle"));
    }
}

TEST_CASE_METHOD(RandomFigureFactoryTestFixture, "RandomFigureFactory creates only figures of allowed type")
{
    factory.registerFigure("circle", std::make_unique<CircleCreator>());

    const size_t figuresCount = 1000;
    for (size_t i = 0; i < figuresCount; i++)
    {
        std::unique_ptr<Figure> f = factory.createFigure();
        const std::string toStr = f->toString();
        std::istringstream is(toStr);
        std::string figureType;
        is >> figureType;

        REQUIRE(figureType == "circle");
    }
}

//I haven't studied statistics but given 100_000 figures and no generated
//triangles e.g. (if they're registered with the factory), I would expect something is wrong
TEST_CASE_METHOD(RandomFigureFactoryTestFixture, "RandomFigureFactory generates figures within expected uniform distribution")
{
    addDefaultCreators();

    const size_t figuresCount = 100000;
    std::map<std::string, size_t> typeCounts;

    for (size_t i = 0; i < figuresCount; i++) 
    {
        std::unique_ptr<Figure> figure = factory.createFigure();
        REQUIRE(figure != nullptr);

        std::string type = figure->toString().substr(0, figure->toString().find(' '));
        typeCounts[type]++;
    }

    REQUIRE(typeCounts["circle"] > 0);
    REQUIRE(typeCounts["triangle"] > 0);    

    double circleRatio = static_cast<double>(typeCounts["circle"]) / figuresCount;
    double triangleRatio = static_cast<double>(typeCounts["triangle"]) / figuresCount;

    double expectedRatio = 0.5;
    double tolerance = 0.1;

    REQUIRE(((circleRatio >= expectedRatio - tolerance) && (circleRatio <= expectedRatio + tolerance)));
    REQUIRE(((triangleRatio >= expectedRatio - tolerance) && (triangleRatio <= expectedRatio + tolerance)));
}
