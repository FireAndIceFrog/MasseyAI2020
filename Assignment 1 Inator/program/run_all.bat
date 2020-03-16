cls
@echo off
@echo ===================================================================================================================================================================================
@echo                                               SEARCH ALGORITHMS  
@echo                                                  2020 version
set INIT_STATE_1="608435127"
set INIT_STATE_2="743286051"
set INIT_STATE_3="647850321"
set INIT_STATE_4="185024367"
set INIT_STATE_5="867254301"
set GOAL_STATE="123456780"
@echo ===================================================================================================================================================================================
@echo NUM ALGORITHM                  INIT_STATE  GOAL_STATE   PATH_LENGTH	STATE_EXPANSIONS    MAX_QLENGTH	 RUNNING_TIME  DELETIONS_MIDDLE_HEAP LOCAL_LOOPS_AVOIDED ATTEMPTED_REEXPANSIONS COMMENTS
@echo ===================================================================================================================================================================================
main.exe "batch_run" "pds_visited_list"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "pds_visited_list"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "pds_visited_list"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "pds_visited_list"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "pds_visited_list"      %INIT_STATE_5% %GOAL_STATE%

main.exe "batch_run" "pds_nonstrict_visited_list"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "pds_nonstrict_visited_list"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "pds_nonstrict_visited_list"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "pds_nonstrict_visited_list"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "pds_nonstrict_visited_list"      %INIT_STATE_5% %GOAL_STATE%

main.exe "batch_run" "best_first_no_visited_list"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "best_first_no_visited_list"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "best_first_no_visited_list"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "best_first_no_visited_list"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "best_first_no_visited_list"      %INIT_STATE_5% %GOAL_STATE%

main.exe "batch_run" "best_first_visited_list"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "best_first_visited_list"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "best_first_visited_list"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "best_first_visited_list"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "best_first_visited_list"      %INIT_STATE_5% %GOAL_STATE%

main.exe "batch_run" "astar_explist_manhattan"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "astar_explist_manhattan"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "astar_explist_manhattan"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "astar_explist_manhattan"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "astar_explist_manhattan"      %INIT_STATE_5% %GOAL_STATE%

main.exe "batch_run" "astar_explist_misplacedtiles"      %INIT_STATE_1% %GOAL_STATE%
main.exe "batch_run" "astar_explist_misplacedtiles"      %INIT_STATE_2% %GOAL_STATE%
main.exe "batch_run" "astar_explist_misplacedtiles"      %INIT_STATE_3% %GOAL_STATE%
main.exe "batch_run" "astar_explist_misplacedtiles"      %INIT_STATE_4% %GOAL_STATE%
main.exe "batch_run" "astar_explist_misplacedtiles"      %INIT_STATE_5% %GOAL_STATE%


@echo nothing follows.

