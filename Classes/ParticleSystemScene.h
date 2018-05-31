#ifndef __PARTICLESYSTEM_SCENE_H__
#define __PARTICLESYSTEM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "cparticlesystem.h"
#include "Common/CSwitchButton.h"
#include  "Common/CDraggableSprite.h"


class ParticleSystemScene : public cocos2d::Layer
{
private:
	// 分子的可提整不同參數的顯示
	cocos2d::ui::TextBMFont *_GravityBMValue;
	cocos2d::ui::TextBMFont *_SpreadBMValue;
	cocos2d::ui::TextBMFont *_DirectionBMValue;
	cocos2d::ui::TextBMFont *_SpinBMValue;
	cocos2d::ui::TextBMFont *_OpacityBMValue;
	cocos2d::ui::TextBMFont *_ParticlesBMValue;
	cocos2d::ui::TextBMFont *_SpeedBMValue;
	cocos2d::ui::TextBMFont *_LifetimeBMValue;
	cocos2d::ui::TextBMFont *_RedBMValue;
	cocos2d::ui::TextBMFont *_GreenBMValue;
	cocos2d::ui::TextBMFont *_BlueBMValue;
	cocos2d::ui::TextBMFont *_WindBMValue;
	//button listener
	cocos2d::ui::Button *_cuberbtn;
	cocos2d::ui::Button *_cuberbtn2;
	cocos2d::ui::Button *_cuberbtn3;

	// 選擇不同的分子型態，用在 Emitter 沒有開啟的狀態
	cocos2d::ui::TextBMFont *_TypeBMValue;
	cocos2d::ParticleSystem *_particletaki;
	cocos2d::ParticleSystem *_particlesnow;
	cocos2d::ParticleSystem *_particlegalaxy3;
	// For Emitter
	CDraggableSprite *_EmitterSprite;
	bool _bEmitterOn;
	CSwitchButton *_emitterSwitchBtn;

	//For Other Particle effect
	CSwitchButton *_bubbleSwitchBtn;
	CSwitchButton *_circleSwitchBtn;
	CSwitchButton *_cloudSwitchBtn;
	CSwitchButton *_flareSwitchBtn;
	CSwitchButton *_raindropSwitchBtn;
	CSwitchButton *_cometSwitchBtn;
	CSwitchButton *_sparkSwitchBtn;

	bool _bcuberbtn;
	bool _bcuberbtn2;
	bool _bcuberbtn3;

	//Three emittereffect For Emitter
	CSwitchButton *_emitter01SwitchBtn;
	CSwitchButton *_emitter02SwitchBtn;
	CSwitchButton *_emitter03SwitchBtn;
	CSwitchButton *_emitter04SwitchBtn;

	bool _bEmitter01On;
	bool _bEmitter02On;
	bool _bEmitter03On;
	bool _bEmitter04On;
	float _fEmitter01Time;
	float _fEmitter02Time;
	float _fEmitter03Time;
	float _fEmitter04Time;

	//EmitterEffect
	bool _emitterEffectOn;
	float _emitterEffectCTime;
	CSwitchButton *_EmitterEffectSwitchBtn;
public:

	CParticleSystem _ParticleControl;

	~ParticleSystemScene();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void doStep(float dt);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	//button
	void CuberBtnTouchEvent(Ref *pSender, cocos2d::ui::Button::TouchEventType type);
	void CuberBtnTouchEvent2(Ref *pSender, cocos2d::ui::Button::TouchEventType type);
	void CuberBtnTouchEvent3(Ref *pSender, cocos2d::ui::Button::TouchEventType type);

	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(ParticleSystemScene);
};

#endif // __MAIN_SCENE_H__
