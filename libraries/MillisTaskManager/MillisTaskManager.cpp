/*
 * MIT License
 * Copyright (c) 2018-2020 _VIFEXTech
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the follo18wing conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "MillisTaskManager.h"

#ifndef NULL
#   define NULL 0
#endif

#define TASK_NEW(task) do{task = new Task_t;}while(0)
#define TASK_DEL(task) do{delete task;}while(0)

/**
  * @brief  ��ʼ�������б�
  * @param  priorityEnable:�趨�Ƿ������ȼ�
  * @retval ��
  */
MillisTaskManager::MillisTaskManager(bool priorityEnable)
{
    PriorityEnable = priorityEnable;
    Head = NULL;
    Tail = NULL;
}

/**
  * @brief  �������������ͷ����������ڴ�
  * @param  ��
  * @retval ��
  */
MillisTaskManager::~MillisTaskManager()
{
    /*�ƶ�������ͷ*/
    Task_t* now = Head;
    while(true)
    {
        /*��ǰ�ڵ��Ƿ�Ϊ��*/
        if(now == NULL)
            break;

        /*����ǰ�ڵ㻺�棬�ȴ�ɾ��*/
        Task_t* now_del = now;

        /*�ƶ�����һ���ڵ�*/
        now = now->Next;

        /*ɾ����ǰ�ڵ��ڴ�*/
        TASK_DEL(now_del);
    }
}

/**
  * @brief  �������������һ�������趨���ִ��ʱ��
  * @param  func:������ָ��
  * @param  timeMs:����ʱ���趨(����)
  * @param  state:���񿪹�
  * @retval ����ڵ��ַ
  */
MillisTaskManager::Task_t* MillisTaskManager::Register(TaskFunction_t func, uint32_t timeMs, bool state)
{
    /*Ѱ�ҵ�ǰ����*/
    Task_t* task = Find(func);
    
    /*�����ע��*/
    if(task != NULL)
    {
        /*������Ϣ*/
        task->Time = timeMs;
        task->State = state;
        return task;
    }

    /*Ϊ�����������ڴ�*/
    TASK_NEW(task);

    /*�Ƿ�����ɹ�*/
    if(task == NULL)
    {
        return NULL;
    }

    task->Function = func;        //����ص�����
    task->Time = timeMs;          //����ִ������
    task->State = state;          //����״̬
    task->TimePrev = 0;           //��һ��ʱ��
    task->TimeCost = 0;           //ʱ�俪��
    task->TimeError = 0;          //���ʱ��
    task->Next = NULL;            //��һ���ڵ�
    
    /*�����������Ϊ��*/
    if(Head == NULL)
    {
        /*����ǰ������Ϊ�����ͷ*/
        Head = task;
    }
    else
    {
        /*����������β���������*/
        Tail->Next = task;
    }
    
    /*����ǰ������Ϊ�����β*/
    Tail = task;
    return task;
}

/**
  * @brief  Ѱ������,��������ڵ�
  * @param  func:������ָ��
  * @retval ����ڵ��ַ
  */
MillisTaskManager::Task_t* MillisTaskManager::Find(TaskFunction_t func)
{
    Task_t* now = Head;
    Task_t* task = NULL;
    while(true)
    {
        if(now == NULL)//��ǰ�ڵ��Ƿ�Ϊ��
            break;

        if(now->Function == func)//�жϺ�����ַ�Ƿ����
        {
            task = now;
            break;
        }

        now = now->Next;//�ƶ�����һ���ڵ�
    }
    return task;
}

/**
  * @brief  ��ȡ��ǰ�ڵ��ǰһ���ڵ�
  * @param  task:��ǰ����ڵ��ַ
  * @retval ǰһ������ڵ��ַ
  */
MillisTaskManager::Task_t* MillisTaskManager::GetPrev(Task_t* task)
{
    Task_t* now = Head;    //��ǰ�ڵ�
    Task_t* prev = NULL;   //ǰһ�ڵ�
    Task_t* retval = NULL; //�����صĽڵ�
    
    /*��ʼ��������*/
    while(true)
    {
        /*�����ǰ�ڵ�Ϊ��*/
        if(now == NULL)
        {
            /*��������*/
            break;
        }
        
        /*�����ǰ�ڵ��뱻�����Ľڵ�ƥ��*/
        if(now == task)
        {
            /*����ǰһ���ڵ㣬׼������*/
            retval = prev;
            break;
        }
        
        /*��ǰ�ڵ㱣��Ϊǰһ�ڵ�*/
        prev = now;
        
        /*�ڵ����*/
        now = now->Next;
    }
    return retval;
}

/**
* @brief  ע�����񣨽���ʹ�ã��̲߳���ȫ��
  * @param  func:������ָ��
  * @retval true:�ɹ� ; false:ʧ��
  */
bool MillisTaskManager::Logout(TaskFunction_t func)
{
    Task_t* task = Find(func);
    if(task == NULL)
        return false;

    Task_t* prev = GetPrev(task); //ǰһ���ڵ�
    Task_t* next = task->Next;    //��һ���ڵ�
    
    /*�����ɾ���ڵ�������ͷ*/
    if(prev == NULL && next != NULL)
    {
        /*����һ���ڵ���Ϊ����ͷ*/
        Head = next;
    }
    /*�����ɾ���ڵ�������β*/
    else if(prev != NULL && next == NULL)
    {
        /*��ǰһ���ڵ���Ϊ����β*/
        prev->Next = NULL;
    }
    /*�����ɾ���ڵ��������м�*/
    else if(prev != NULL && next != NULL)
    {
        /*��ǰһ���ڵ�Խ�����һ���ڵ�*/
        prev->Next = next;
    }
    /*���ֻ�е�ǰһ���ڵ�*/
    else if (prev == NULL && next == NULL) {
        Head = NULL;
    }
    
    /*ɾ����ǰ�ڵ�*/
    TASK_DEL(task);
    
    return true;
}

/**
  * @brief  ����״̬����
  * @param  func:������ָ��
  * @param  state:����״̬
  * @retval true:�ɹ� ; false:ʧ��
  */
bool MillisTaskManager::SetState(TaskFunction_t func, bool state)
{
    Task_t* task = Find(func);
    if(task == NULL)
        return false;

    task->State = state;
    return true;
}

/**
  * @brief  ����ִ����������
  * @param  func:������ָ��
  * @param  timeMs:����ִ������
  * @retval true:�ɹ� ; false:ʧ��
  */
bool MillisTaskManager::SetIntervalTime(TaskFunction_t func, uint32_t timeMs)
{
    Task_t* task = Find(func);
    if(task == NULL)
        return false;

    task->Time = timeMs;
    return true;
}

#if (MTM_USE_CPU_USAGE == 1)
#include "Arduino.h"                //��Ҫʹ��micros()
static uint32_t UserFuncLoopUs = 0; //�ۼ�ʱ��
/**
  * @brief  ��ȡCPUռ����
  * @param  ��
  * @retval CPUռ���ʣ�0~100%
  */
float MillisTaskManager::GetCPU_Usage()
{
    static uint32_t MtmStartUs;
    float usage = (float)UserFuncLoopUs / (micros() - MtmStartUs) * 100.0f;

    if(usage > 100.0f)
        usage = 100.0f;

    MtmStartUs = micros();
    UserFuncLoopUs = 0;
    return usage;
}
#endif

/**
  * @brief  ʱ����ж�
  * @param  nowTick:��ǰʱ��
  * @param  prevTick:��һ��ʱ��
  * @retval ʱ���
  */
uint32_t MillisTaskManager::GetTickElaps(uint32_t nowTick, uint32_t prevTick)
{
    uint32_t actTime = nowTick;

    if(actTime >= prevTick)
    {
        prevTick = actTime - prevTick;
    }
    else
    {
        prevTick = /*UINT32_MAX*/0xFFFFFFFF - prevTick + 1;
        prevTick += actTime;
    }

    return prevTick;
}

/**
  * @brief  ��ȡ���񵥴κķ�ʱ��(us)
  * @param  func:������ָ��
  * @retval ���񵥴κķ�ʱ��(us)
  */
uint32_t MillisTaskManager::GetTimeCost(TaskFunction_t func)
{
    Task_t* task = Find(func);
    if(task == NULL)
        return 0;

    return task->TimeCost;
}

/**
  * @brief  ������(�ں�)
  * @param  tick:�ṩһ����ȷ�������ϵͳʱ�ӱ���
  * @retval ��
  */
void MillisTaskManager::Running(uint32_t tick)
{
    Task_t* now = Head;
    while(true)
    {
        /*��ǰ�ڵ��Ƿ�Ϊ��*/
        if(now == NULL)
        {
            /*��������*/
            break;
        }

        if(now->Function != NULL && now->State)
        {
            uint32_t elapsTime = GetTickElaps(tick, now->TimePrev);
            if(elapsTime >= now->Time)
            {
                /*��ȡʱ�������Խ��ʵʱ��Խ��*/
                now->TimeError = elapsTime - now->Time;
                
                /*��¼ʱ���*/
                now->TimePrev = tick;

#if (MTM_USE_CPU_USAGE == 1)
                /*��¼��ʼʱ��*/
                uint32_t start = micros();
                
                /*ִ������*/
                now->Function();
                
                /*��ȡִ��ʱ��*/
                uint32_t timeCost = micros() - start;
                
                /*��¼ִ��ʱ��*/
                now->TimeCost = timeCost;
                
                /*��ʱ���ۼ�*/
                UserFuncLoopUs += timeCost;
#else
                now->Function();
#endif
                
                /*�ж��Ƿ������ȼ�*/
                if(PriorityEnable)
                {
                    /*��������*/
                    break;
                }
            }
        }

        /*�ƶ�����һ���ڵ�*/
        now = now->Next;
    }
}