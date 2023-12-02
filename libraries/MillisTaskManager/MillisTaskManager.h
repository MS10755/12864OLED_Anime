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
 
/**
  ******************************************************************************
  * @file    MillisTaskManager.h
  * @author  _VIFEXTech
  * @version v2.1
  * @date    2020-7-23
  * @brief   ����������ʱ����ʽ�������������������ɵ�millis()��ѯ������������ArduinoAPI
  * @Upgrade 2018.7.26  v1.0 ����
  * @Upgrade 2018.10.9  v1.1 ������״̬��־λ���ͻ���bool����
  * @Upgrade 2018.11.17 v1.2 ��typedefת����class�ڲ�
  * @Upgrade 2018.11.18 v1.3 �޸�50�����ֵ�����������ֹͣ��bug
  * @Upgrade 2018.12.17 v1.4 �� TaskCtrl �޸�Ϊ TaskStateCtrl������޸�������ʱ��Ľӿڣ���� TaskFind ���ڱ����б�Ѱ������
  * @Upgrade 2019.2.5   v1.5 ������������������ͷ��ڴ�
  * @Upgrade 2019.3.4   v1.6 ��FuncPos��ΪID�����TaskFind(void_TaskFunction_t Function)
  * @Upgrade 2019.3.21  v1.7 ֧���趨���ȼ������ȼ�����Ϊ����ID�ţ�����ԽС���ȼ�Խ��
  * @Upgrade 2019.4.24  v1.8 ���GetCPU_Useage()�ɻ��CPUռ����
  * @Upgrade 2019.5.8   v1.9 ΪTaskRegister��ӷ���ͻ�ж�
  * @Upgrade 2019.9.3   v2.0 ���TimeCost����ʱ�俪������
  * @Upgrade 2020.7.23  v2.1 ʹ�õ��������������� GetTickElaps ����uint32������⣬���ʱ������¼
  ******************************************************************************
  * @attention
  * ��Ҫ�ṩһ����ȷ�����뼶��ϵͳʱ�ӣ�Ȼ�����ڵ���Running����
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MILLISTASKMANAGER_H
#define __MILLISTASKMANAGER_H

#define MTM_USE_CPU_USAGE 0

#include <stdint.h>

class MillisTaskManager
{
public:
    typedef void(*TaskFunction_t)(void);//����ص�����
    struct Task
    {
        bool State;                //����״̬
        TaskFunction_t Function;   //������ָ��
        uint32_t Time;             //����ʱ��
        uint32_t TimePrev;         //������һ�δ���ʱ��
        uint32_t TimeCost;         //����ʱ�俪��(us)
        uint32_t TimeError;        //���ʱ��
        struct Task* Next;         //��һ���ڵ�
    };
    typedef struct Task Task_t;//�������Ͷ���

    MillisTaskManager(bool priorityEnable = false);
    ~MillisTaskManager();

    Task_t* Register(TaskFunction_t func, uint32_t timeMs, bool state = true);
    Task_t* Find(TaskFunction_t func);
    Task_t* GetPrev(Task_t* task);
    bool Logout(TaskFunction_t func);
    bool SetState(TaskFunction_t func, bool state);
    bool SetIntervalTime(TaskFunction_t func, uint32_t timeMs);
    uint32_t GetTimeCost(TaskFunction_t func);
    uint32_t GetTickElaps(uint32_t nowTick, uint32_t prevTick);
#if (MTM_USE_CPU_USAGE == 1)
    float GetCPU_Usage();
#endif
    void Running(uint32_t tick);

private:
    Task_t* Head;        //��������ͷ
    Task_t* Tail;        //��������β
    bool PriorityEnable; //���ȼ�ʹ��
};

#endif