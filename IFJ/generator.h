/*Implementace překladače imperativního jazyka IFJ18
Jakub Gajdošík xgajdo24
Daniel Bílý xbilyd01
Petr Marek xmarek69
Jan Fridrich xfridr07
*/
#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "scanner.h"



void push_true();
void push_false();
void gen_if_start();
void gen_else();
void gen_if_end();
void gen_while_start();
void gen_while_condition();
void gen_while_end();
void create_frame();
void gen_call(char *fname);
void result_to_var(char *v_name);
void gen_stack_push(token_t token);
void gen_var(char *v_name);
void gen_stack_pop(char *frame, char *v_name);
void generator_init();
void print_output();
void gen_header();
void gen_main_start(); 
void gen_main_end();
void gen_def_start(char *f_name);
void gen_def_end();
void gen_var_from_token(token_t token);
void gen_frame_retvar();
void switch_stack();
void gen_stack_add();
void gen_stack_sub();
void gen_stack_mul();
void gen_stack_div();
void gen_stack_idiv();
void gen_stack_eq();
void gen_stack_less_than();
void gen_less_or_equal();
void gen_more_or_equal();
void gen_not_equal();
void gen_stack_concatanate();
void gen_stack_more_than();
void gen_int2float();
void gen_built_end();
void retvar_to_result();
void gen_argument();
void gen_parametr();



























/*
_____.___.           /\              ___.                            ________                                 .___
\__  |   | ____  __ _)/__  __ ____   \_ |__   ____   ____   ____    /  _____/  ____   ____   _____   ____   __| _/
 /   |   |/  _ \|  |  \  \/ // __ \   | __ \_/ __ \_/ __ \ /    \  /   \  ___ /    \ /  _ \ /     \_/ __ \ / __ | 
 \____   (  <_> )  |  /\   /\  ___/   | \_\ \  ___/\  ___/|   |  \ \    \_\  \   |  (  <_> )  Y Y  \  ___// /_/ | 
 / ______|\____/|____/  \_/  \___  >  |___  /\___  >\___  >___|  /  \______  /___|  /\____/|__|_|  /\___  >____ | 
 \/                              \/       \/     \/     \/     \/          \/     \/             \/     \/     \/ 


                                             ```.....,,,:,.``                                                                                                          
                                         ``.:'++++++++++++++;.`                                                                                                        
                                        `:'+++++++'+++++++++++;::.`                                                                                                    
                                      `:++++++++++++++++++++++++++:                                                                                                    
                                     :'++++++++++++++++++++++++++++,                                                                                                   
                                   `:++++++++++++++++++++++++++++++'```                                                                                                
                                  `;++++++++++++++++++++++++++++++++;.`                                                                                                
                                  :++++++++++++++++++++++++++++++++++++``                                                                                              
                                 `'++++++++++++++++++++++++++++++++++++'.                                                                                              
                                 .+'++++++++++++++++++++++++++++++++++++'`                                                                                             
                                 ;+++++++++++++++++++++++++++++++++++++'+.                                                                                             
                                ;++++++++++++++++++++++++++++++++++++++++,`                                                                                            
                                +'+++++++++++++++++++++++++++++++++++++++;`                                                                                            
                               `++++++++++++++++++++++++++++++++++++++++++.                                                                                            
                               `#+++++++++++++++++++++++++++++++++++++++++'``                                                                                          
                               :++++++++++++++++++++++++++++++++++++++++++++:`                                                                                         
                              `'++++++++++++++++++++++++++++++++++++++++++++#:`                                                                                        
                              ,+++++++++++++++++++++++++++++++++++++++++++++++.                                                                                        
                             `'+++++++++++++++++++++++++++++++++++++++++++++++:                                                                                        
                             :'+++++++++++++++++++++++++++++++++++++++++++++++:                                                                                        
                            ,+++++++++++++++';;;;;;;;;;;;;;;;;'''''+++++++++++:                                                                                        
                            :+++++++++';:,.....,.............,,,,,:...,,,:;'++`                                                                                        
                            :+++++++;:,........,,,,,....,,,,,,,,,,,,,,,,,,,,;'                                                                                         
                            ;+##++#'::,........,,...........,,,,,,,,.........`                                                                                         
                           `,:;'+#+:,:,...........,.,,,,,.,,,,,,,,,,,,,....,.`                                                                                         
                           `..,,:'+.,,,..........,,,,,,,,,,,,,,,,,,,,,,,,,,,,                                                                                          
                           `,,..,,:..,,,.........,,,,,,,,,,,,,,,,,,:,,,,,,,,.                                                                                          
                           `:::,,,,...,,,.......,.,,::::::,,,,,,,::::,,,,,,,`                                                                                          
                           `:::::,,.....,.......,,::''++;;;:,,,,:'+++:,,,,,,.`                                                                                         
                           `,::;;;,.....,.......,,:;#+#'+;';:,,,;###''::,,.,.`                                                                                         
                            .:::;;:,....,,.....,,,:'#+##+;':,,,,:###+':,,,.,.`                                                                                         
                             ,::;:,,....,,.....,,,,,'+##';:::,,,::'++;:,,,.,.`                                                                                         
                             .::;:,:,...,,.....,,,,,,,,,,,,:,::,:,,,,,:,,,.,.`                                                                                         
                              ,,::,:,..,,,.,.,,,,,,,,,,,,,,,,:,:,,,,,,,,,....`                                                                                         
                              .,,,,:,..,,,..,,,,,,,,,,,,,,,::::,,,,,,,,,,,.,.`                                                                                         
                              `,,,,::..,,,...,,,,,,,,,,,,,,::::,,,,,,,,,,,...`                                                                                         
                               .,,,:;..,,,...,,,,,,,,,,,,,,::,,,,,,,,,,,,,...`                                                                                         
                               .,,,::...,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,...                                                                                         
                               `,,::,...,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,....                                                                                         
                                .,:,,...,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,`                                                                                        
                                .,:,,...,,,,,,,,,,,,,,,,,,:,,,,,,,,,,,,,,,...,`                                                                                        
                                 ,;:,......,,,,,,,,,,,,::::::,,::::,,,,,,......                                                                                        
                                 `;',.......,::,,,,.,,,,,,,:;';;;;;,,,.........                                                                                        
                                .'#+..........,,,,,,.,,,.,,,,,,:,,,,...........                                                                                        
                               ,###+........,.,,.,,,,,,,,,,,,,,,,...........,..                                                                                        
                              ;####'............,,,,,,,,,,,,,,,,,:::,,.......,.                                                                                        
                            `+##++++............,,,,,::::;'+++++''';:,.......,.                                                                                        
                           `+##+++++,...........,,,,,,,,,::;;;;;;;::,........,.                                                                                        
                          `'#+++++++'...,.......,,,,,,,,::::::,,::::...........                                                                                        
                         `####++++++;.............,,,,,,:::::::;:,.............                                                                                        
                       ` '######+++++,.,...........,,,,,,,,,,,,,,,,,,,,......,.                                                                                        
                        ;########+++#;.,............,,,,,,,,,,,,,,,,,,,......,`                                                                                        
                       :#########+++++,.............,,,,,,,,,,,,,,,,,,,.......`                                                                                        
                      :#+########++++++:,.....................................`                                                                                        
                     :#+#########+++++++......................................`                                                                                        
                    `+############++++++:.,...................................;`                                                                                       
                   `'#############+++++#+,...................................,##:.``.,,,.                                                                              
                   ;#+############+++++++'...................................:###########'                                                                             
                  .++#+###########++++++#+,..................................;#########+##.                                                                            
                  ;+++++##########+++++++#:................................`;######++++++#,                                                                            
                 `'+++++##########+++++++++...............................`.+#####++++++##'       ```.`                                                                
                 `+++++++#########++++++++++:.............................`,######++++++''+.   `.,,,:::,.`                                                             
                 ,+++++++#########+++++++++++:.............................;######++++';:,,,::,,,,,,,,:;;::.`                                                          
                 '+++++++++#######+++++++++++;`...........................'#######++++;;::,,,,,,,,,,::,:;;;;:.`                                                        
                :+++++++++########++++++++++++:...........................+#######++++;::,,,,,,,,,,,,;;;::::;;,`                                                       
               .#+++++###+########++++++++++++###',......................,+#######++++;::,,,,:::::::,,::;;;::::`                                                       
               '++#+'''+##########+++++++++++++++##;.,................,.,;########++++;:,,,:,::::,;'::,:::;;;:,`                                                       
              .+#+#+;;::;+#########+++++++++++++++#+++##':...........;+++#########++++;,,,,,,,::,,,;'';;;:,:;;:,`                                                      
              ,+###';:,:::;;++;;;'++++'+++++++++++++++++#+:.```.``.:+++++++#######+++++:,,,,,:::,:,,:;';;;:,,,::`                                                      
              .####;::::::::::,::,,,,,,:'+++++++++++++++++++###+++#++++++++#######++++###';,,::::,,,,,,::::;:,,,`                                                      
              `####;,,,,,::::::::::::::,:#++++++++++++++++++++++++++++++++++#######+++####+``,,,,,,,,,,,,,,.,:::.                                                      
              `####;,,:,,,:::::::::::::.:#+++++++++++++++++++++++++++++++++++######+++####`  `,,:,,,,,,,,,,,.`,,.                                                      
               +###',,,,,::::::::::;++++++++++++++++++++++++++++++++++++++++########+++##+`   .:,,.```..,,,,,``                                                        
               +#+#',,,,,:,,,:,:::::'##+++++++++++++++++++++++++++++++++++++:###########'.     .::,`     .,,,                                                          
               '#++',,,,,,,::,,,:::::;'#++++++++++++++++++++++++++++++++++++ .+##+#####+`      `,::.      ```                                                          
               '#++',,,,,,,:::;;:::::,:;'+++++++++++++++++++++++++++++++++++   `,'#####,        `:,:`                                                                  
               :##++,,,,,,:::::;'';::::::,'#++++++++++++++++++++++++++++++++       ``.`          `:,:`                                                                 
               ,###+:,,,,,,:::::;''+;::::::++++++++++++++++++++++++++++++++'                      `,::.                                                                
               .####',,,,,,:::,:::;+##+':,:+++++++++++++++++++++++++++++++#:                       `,,,                                                                
                '####::,,,,,:::,,::;'###+++++++++++++++++++++++++++++++++++`                        `,,                                                                
                `;':.`,,,,,,:;;;:::,:;+##+++++++++++++++++++++++++++++++++:                          ``                                                                
                      `:,:,,,,;''':,,,:::;+++++++++++++++++++++++++++++++'`                                                                                            
                       .:,:::::;''';,:::::##+###++++++++++++++++++++++++#.                                                                                             
                        ,,::;;:::;'+';:::'#######++++++++++++++++++++++',                                                                                              
                        `:::;'';:::;+######+######+++++++++++++++++++++`                                                                                               
                         `,::;'+';:::;++#++++++++++++++++++++++++++++++  `                                                                                             
                           `,::''++::::;#++++++++++++++++++++++++++++++.                                                                                               
                            ,:,:;;++;,:,++++++++++++++++++++++++++++++#,                                                                                               
                            ;..;,:;'#;,:#++++++++++++++++++++++++++++++:                                                                                               
                           `' .#+:,:;++++++++++++++++++++++++++++++++++'                                                                                               
                           `, ,#++:,:++++++++++++++++++++++++++++++++++'                                                                                               
                           ,. ;#+##+++++++++++++++++++++++++++++++++++++`                                                                                              
                           ;  ++++#++++++++++++++++++++++++++++++++++++#`                                                                                              
                           ;  '++++++++++++++++++++++++++++++++++++++++#`                                                                                              
                           `  ;++++++++++++++++++++++++++++++++++++++#;.                                                                                               
                              ;#+#++++++++++++++++++++++++++++++++++++                                                                                                 
                              `'#+###++++++++++++#+####++++++++++++++#`                                                                                                
                               `+++++++++++++++++++++#####+##++++++++;                                                                                                 
                                ,#+++++++++++++++#++#+#########++++++,                                                                                                 
                                 '++++++++++++++++#',@#########+++++#.                                                                                                 
                                 .+++++++++++++++##, '#########+++++#`                                                                                                 
                                  ++++++++++++++++#. :#########++++++                                                                                                  
                                  :++++++++++++++++  ,#########++++#;                                                                                                  
                                  `+++++++++++++++'  `########++++++:                                                                                                  
                                   +++++++++++++++,  `########++++++,                                                                                                  
                                   '+++++++++++++#, `,########+++++#.                                                                                                  
                                   '+++++++++++++#. `'+#######++++++`                                                                                                  
                                   '++++++++++++#+..##########+++++; `                                                                                                 
                                  `+++++++++++++++:@##########+++++:                                                                                                   
                                  :#++++++++++++++ @##########++++++, `                                                                                                
                                '+#+++++++++++++#+ +#########+++#####;                                                                                                 
                                '##+++++++++++++++:.@@##############@.                                                                                                 
                                ,@#######+++++++##@#@@@@###########@'                                                                                                  
                                `@#################''@@#############.                                                                                                  
                                 '################@,,@@@###########'                                                                                                   
                                 ,@###############+` ##############.                                                                                                   
                                 `@##############@:  +##########@#'                                                                                                    
                                  +###############`  :@@#######@##:                                                                                                    
                                  '#############@'```,@########@#+`                                                                                                    
                          ````````;@##########@##.```.@#########@;                                                                                                     
                        `````......#############+.....#@########@,`````    `````                                                                                       
                        ````.......+###########@:....,#########@#````````````````                                                                                      
                        ```........'###########+....`,@##########.`````````````````                                                                                    
                       ```.........'###########;`....;@#########@;````````````````````                                                                                 
    `````````````      ```....,,,,.'###########:....;@###########@;``````````````````````                                                                              
    `````````````````````....,,,,,.;@##########.`...##@@########@##'``.`````````````````````````                                                                       
   `````````````````````....,,,,,,.'###########....,#@###############',`.`````````````````````````````                                                                 
   `````````````````````....,,,,,,:############+...,@##############@#@##:``.````````````````````````````                                                               
   ````````````````````.....,,,,,,###############,,.@#################@###,`.````````````````````````````                                                              
   `````````................,,,,,:#############@##,.#@####################+`..````````````````````````````                                                             
   ```...........................;###############@#'#@####################@.``...........````````````````                                                              
   ```...........................;################@@#@####################@:.`...........`````````````````                                                             
 ````.........................``.:##@###########@##########################'``...........`````````````````                                                             
````..........................```.@#####################@#@@################`............```````````````````````                                                       
````..........................```.@#####################+..,###############@`............````````````````````````                                                      
````..........................```.#######################.``,#@#############`............````````````````````````                                                      
`````.........................````######################@,`.`.############@#`......,,,...````````````````````````                                                      
`````````.....................````,'#@@##################;``.`.,:'+@@@@@#;,`......,,,....````````````````````````                                                      
`````````.....................``````..;+@################+```..``````...```.`.....,,,,...````````````````````````                                                      
`````````.....................```````.`.#################+```.`````````..``.......,,,,...````````````````````````                                                      
`````````.....................````````.`:#@##############'`..`````.`````````..............```````````````````````                                                      
`````````.....................```````````.'#@##########@#:``````````````````..............```````````````````````                                                      
``````````....................`````````````.,;########+:.```````````````````.............````````````````````````                                                      
```````````.........`````````````````````.``...```````.``````````````````````````````````````````````````````````                                                      
         ````````````````````````````````````````````````````````````````````````````````````````````````````````                                                      
          ```````````````````````````````````````````````````````````````````````````````       ````````````                                                           
            ``````````````````````````````````````````````````````````````````````````                     
*/