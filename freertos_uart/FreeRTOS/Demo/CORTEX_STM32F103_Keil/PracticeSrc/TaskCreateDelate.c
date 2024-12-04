/**
 ****************************************************************************************************
 * @file        freertos.c
 * @author      ??????????(ALIENTEK)
 * @version     V1.4
 * @date        2022-01-04
 * @brief       FreeRTOS ??????
 * @license     Copyright (c) 2020-2032, ??????????????????????
 ****************************************************************************************************
 * @attention
 *
 * ?????:??????? F407?????????
 * ???????:www.yuanzige.com
 * ???????:www.openedv.com
 * ??????:www.alientek.com
 * ??????:openedv.taobao.com
 *
 ****************************************************************************************************
 */



/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "TaskCreateDelate.h"

/******************************************************************************************************/
/*FreeRTOS????*/

/* START_TASK ???? ????
 * ????: ?????? ????????? ?????? ????????
 */
#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE   128
TaskHandle_t    start_task_handler;
void start_task( void * pvParameters );

/* TASK1 ???? ????
 * ????: ?????? ????????? ?????? ????????
 */
#define TASK1_PRIO         2
#define TASK1_STACK_SIZE   128
TaskHandle_t    task1_handler;
void task1( void * pvParameters );

/* TASK2 ???? ????
 * ????: ?????? ????????? ?????? ????????
 */
#define TASK2_PRIO         3
#define TASK2_STACK_SIZE   128
TaskHandle_t    task2_handler;
void task2( void * pvParameters );

/* TASK3 ???? ????
 * ????: ?????? ????????? ?????? ????????
 */
#define TASK3_PRIO         4
#define TASK3_STACK_SIZE   128
TaskHandle_t    task3_handler;
void task3( void * pvParameters );
/******************************************************************************************************/


/**
 * @brief       FreeRTOS??????????
 * @param       ??
 * @retval      ??
 */
void freertos_demo(void)
{    
    xTaskCreate((TaskFunction_t         )   start_task,
                (char *                 )   "start_task",
                (configSTACK_DEPTH_TYPE )   START_TASK_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   START_TASK_PRIO,
                (TaskHandle_t *         )   &start_task_handler );
    vTaskStartScheduler();
}


void start_task( void * pvParameters )
{
    taskENTER_CRITICAL();               /* 进入临界区 */
    xTaskCreate((TaskFunction_t         )   task1,
                (char *                 )   "task1",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &task1_handler );
                
    xTaskCreate((TaskFunction_t         )   task2,
                (char *                 )   "task2",
                (configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK2_PRIO,
                (TaskHandle_t *         )   &task2_handler );
                
    xTaskCreate((TaskFunction_t         )   task3,
                (char *                 )   "task3",
                (configSTACK_DEPTH_TYPE )   TASK3_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK3_PRIO,
                (TaskHandle_t *         )   &task3_handler );
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* 退出临界区 */
}

/* ??????????LED0?500ms?????? */
void task1( void * pvParameters )
{
    while(1)
    {
        printf("task1?????????????\r\n");
        vTaskDelay(500);
    }
}

/* ??????????LED1?500ms?????? */
void task2( void * pvParameters )
{
    while(1)
    {
        printf("task2?????????????\r\n");
        vTaskDelay(500);
    }
}

/* ??????????????KEY0??????KEY0???task1 */
void task3( void * pvParameters )
{
    uint8_t key = 0;
    while(1)
    {
        printf("task3?????????????\r\n");
        if(key == 1)
        {
            if(task1_handler != NULL)
            {
                printf("???task1????\r\n");
                vTaskDelete(task1_handler);
                task1_handler = NULL;
            }

        }
        vTaskDelay(10);
    }
}


