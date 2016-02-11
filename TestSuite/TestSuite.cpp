/* This source file is part of the concurrent Fiber based Framework.
*
* Copyright (c) 2015-2016 Joshua Chew
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "stdafx.h"
#include "../Thread/ForwardDeclarations.h"
#include "../Thread/ThreadManager.h"
#include "../Thread/JobScheduler.h"
#include "gtest/gtest.h"

int main(int argc, char ** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ::testing::InitGoogleTest(&argc, argv);

    ThreadManager threadMnger;
    GET_SINGLETON(JobScheduler).Initialise();
    threadMnger.Initialise();
    threadMnger.RunThreads();
    
    int returnVal = RUN_ALL_TESTS();

    return returnVal;
}

