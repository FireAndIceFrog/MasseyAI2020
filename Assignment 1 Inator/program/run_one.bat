cls
@echo off
@echo ==============================================================================================================
@echo                                               SEARCH ALGORITHMS 
@echo ==============================================================================================================

@echo (1) pds_visited_list
@echo (2) pds_nonstrict_visited_list
@echo (3) best_first_no_visited_list
@echo (4) best_first_visited_list
@echo (5) astar_explist_manhattan
@echo (6) astar_explist_misplacedtiles

echo.
set /p selection="Select Algorithm: "
@echo You picked Algorithm # %selection%

echo.
@echo ==============================================================================================================
@echo INIT_STATE (1): 608435127, GOAL_STATE: 123456780 
@echo INIT_STATE (2): 743286051, GOAL_STATE: 123456780
@echo INIT_STATE (3): 628035471, GOAL_STATE: 123804765
@echo INIT_STATE (4): 041532786, GOAL_STATE: 123456780
@echo INIT_STATE (5): 835642107, GOAL_STATE: 123456780

echo.
set /p testcase="Select Test Case: "
@echo You picked Test case # %testcase%


if %selection% == 1 (
    set param1= single_run pds_visited_list
) else if %selection% == 2 (
    set param1= single_run pds_nonstrict_visited_list
) else if %selection% == 3 (
    set param1= single_run best_first_no_visited_list
) else if %selection% == 4 (
    set param1= single_run best_first_visited_list
) else if %selection% == 5 (
    set param1= single_run astar_explist_manhattan
) else if %selection% == 6 (
    set param1= single_run astar_explist_misplacedtiles
)



if %testcase% == 1 (    
    set param2= 087654321 123456780
        
) else if %testcase% == 2 (
    set param2= 743286051 123456780
    
) else if %testcase% == 3 (
    set param2= 628035471 123804765
    
) else if %testcase% == 4 (
   set param2= 041532786 123456780
    
) else if %testcase% == 5 (
    set param2= 835642107 123456780

) 

set param=%param1% %param2%
echo %param%
main.exe %param%

@echo ==============================================================================================================
@echo nothing follows.

