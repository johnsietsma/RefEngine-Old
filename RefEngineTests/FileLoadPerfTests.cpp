#include "gtest/gtest.h"

#include "file/FBXFile.h"

#include <chrono>
#include <iostream>
#include <string>

using namespace std;

struct Timer
{
    Timer( string name, int reps=1 ) :
        m_name(name),
        m_start(chrono::steady_clock::now()),
        m_reps(reps)
    {
    }
    
    ~Timer()
    {
        double elapsed = GetElapsed();
        cout << m_name << " - Elapsed:" << elapsed << " ms.";
        if( m_reps > 1 ) {
            cout << " Average:" << (elapsed/m_reps) << " ms.";
        }
        cout << endl;
    }
    
    double GetElapsed() const
    {
        chrono::duration<double,std::milli> duration = chrono::steady_clock::now()-m_start;
        return duration.count();
    }
    
    double GetAverage() const
    {
        return GetElapsed() / m_reps;
    }
    
    string m_name;
    chrono::time_point<chrono::steady_clock> m_start;
    int m_reps;
};

double RunAverage( const char* name, const char* fbxFile, int reps )
{
    Timer timer(name, reps);
    
    for( int i=0; i<reps; i++ ) {
        FBXFile file;
        file.load(fbxFile);
    }
    
    return timer.GetAverage();
}

TEST(fbx_perf_test, test_cube)
{
    // MacOS, debug:
    // No changes: 85.2ms
    // Reserve verts, indices: 85.6ms
    // Refactor: 116.8ms.
    
    // Release:
    // No changes: 29.6ms
    // Reserve: 23.6ms
    // Refactor: 32ms
    
    double average = RunAverage( "Cube", "assets/cube/cube.fbx", 10 );
    EXPECT_LE(average, 150);
}

TEST(fbx_perf_test, test_dragon)
{
    // MacOS, debug:
    // No changes: 831.798ms.
    // Reserve verts, indices: 818.64ms
    // Refactor: 228.6ms.
    
    // Release:
    // No changes: 256.9ms.
    // Reserve: 230.6ms.
    // Refactor: 80ms.
    
    
    double average = RunAverage( "Dragon", "assets/dragon/Dragon.fbx", 10 );
    EXPECT_LE(average, 850);
}