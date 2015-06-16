/****************************************************************************
* File Name          : Pubsub.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : This module will implements the base publisher and subscriber model
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/

#ifndef PUBSUB_H
#define PUBSUB_H

#include "Generic/GenericTypeDef.h"
#include "Peripherals/TimerInterface.h"
#include "Containers/JCVect.h"
#include "Containers/CircularBuffer.h"

class Publisher;
class Subscription;
class Subscriber;

class Subscription
{
	//friend class Subscriber;
	friend class Publisher;
	
	public:
		static void Boot(uint8_t max_num_subscriptions);
		//static bool isInitialized(){return Subscription::initialized;};
		static void UnsubscribeAll(Subscriber* sub);
		static uint32_t getDownSample(int8_t iSub);
		
		uint32_t getDownSample(){return DownSample;};
		//bool isActive();
		Publisher* getPublisher(){return pPublisher;};
		Subscriber* getSubscriber(){return pSubscriber;};

	protected:
		//Functions called by Publisher
		void CallUpdate(Publisher* pub);
		void Clear();
		static Subscription* SetNew(Publisher* pub, Subscriber* sub, uint32_t num_downsample);
		void Set(uint32_t num_downsample);

  private:
		Subscription();
		~Subscription(){};  
		void Set(Publisher* publisher, Subscriber* subscriber, uint32_t downsample);
			
		Publisher* pPublisher;
		Subscriber* pSubscriber;
	
		uint32_t DownSample;
		uint32_t SampleNum;
			
		static bool initialized;
		static vector<Subscription*>* Subscriptions;
		static Subscription* getSubscription(int8_t idx); 
		static int8_t findOpenSlot();
		
};

class Subscriber
{
public:
  virtual void update(Publisher* who) = 0;
  void Unsubscribe(Publisher* publisher);
	void UnsubscribeAll();
protected:
	Subscriber();
	
private:
	~Subscriber();
};


class Publisher
{
public:
		void Subscribe(Subscriber* s, uint32_t num_downsample);
		//void NotifySubs(void* what);
		void NotifySubs();
		virtual void pushValue(Buffer* destBuf) = 0; //Function that subscribers can call to get the new data

		void Unsubscribe(Subscriber* s);
		void UnsubscribeAll();
		
		void PushPubDataToBuf(Buffer* buf);
		int8_t findSubscriptionIndex(Subscriber* subscriber);
		void setExpectedPeriod(uint32_t period_us){FullPeriod = period_us;};
		uint32_t getFullPeriod(){return FullPeriod;};
		uint32_t getExpectedPeriod(uint8_t iSub);
		uint32_t getExpectedPeriod(Subscriber* subscriber);
		uint32_t getDownSample(uint8_t iSub);
	
protected:
		Publisher(uint8_t max_num_subscriptions);
		
private:
	 ~Publisher();
		vector<Subscription*>* MySubscriptions;	//Make this private
		uint32_t FullPeriod; //Period (uS)
		
};

#endif




