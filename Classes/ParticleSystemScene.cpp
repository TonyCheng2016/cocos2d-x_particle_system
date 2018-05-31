#include "ParticleSystemScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

Scene* ParticleSystemScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ParticleSystemScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

ParticleSystemScene::~ParticleSystemScene()
{
	this->removeAllChildren();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

// on "init" you need to initialize your instance
bool ParticleSystemScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

	// For Emitter
	_EmitterSprite = CDraggableSprite::create();
	_EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	_EmitterSprite->setVisible(false);
	_bEmitterOn = false;
	this->addChild(_EmitterSprite, 5);

	auto emiterpos = (Sprite *)(rootNode->getChildByName("emitterpos"));
	Point loc = emiterpos->getPosition();
	emiterpos->setVisible(false);
	_emitterSwitchBtn = CSwitchButton::create();
	_emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc);
	this->addChild(_emitterSwitchBtn, 2);

	//========EmitterEffect=============================
	_bEmitter01On = false;
	_fEmitter01Time = 0.0f;
	auto emitter01pos = (Sprite *)(rootNode->getChildByName("emitter_01"));
	Point emitter01loc = emitter01pos->getPosition();
	emitter01pos->setVisible(false);
	_emitter01SwitchBtn = CSwitchButton::create();
	_emitter01SwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", emitter01loc);
	this->addChild(_emitter01SwitchBtn, 2);

	_bEmitter02On = false;
	_fEmitter02Time = 0.0f;
	auto emitter02pos = (Sprite *)(rootNode->getChildByName("emitter_02"));
	Point emitter02loc = emitter02pos->getPosition();
	emitter02pos->setVisible(false);
	_emitter02SwitchBtn = CSwitchButton::create();
	_emitter02SwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", emitter02loc);
	this->addChild(_emitter02SwitchBtn, 2);

	_bEmitter03On = false;
	_fEmitter03Time = 0.0f;
	auto emitter03pos = (Sprite *)(rootNode->getChildByName("emitter_03"));
	Point emitter03loc = emitter03pos->getPosition();
	emitter03pos->setVisible(false);
	_emitter03SwitchBtn = CSwitchButton::create();
	_emitter03SwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", emitter03loc);
	this->addChild(_emitter03SwitchBtn, 2);

	_bEmitter04On = false;
	_fEmitter04Time = 0.0f;
	auto emitter04pos = (Sprite *)(rootNode->getChildByName("emitter_04"));
	Point emitter04loc = emitter04pos->getPosition();
	emitter04pos->setVisible(false);
	_emitter04SwitchBtn = CSwitchButton::create();
	_emitter04SwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", emitter04loc);
	this->addChild(_emitter04SwitchBtn, 3);

	//-------------------------切換分子圖片------------------------------
	auto bubblepos = (Sprite *)(rootNode->getChildByName("bubble"));
	Point bubbleloc = bubblepos->getPosition();
	bubblepos->setVisible(false);
	_bubbleSwitchBtn = CSwitchButton::create();
	_bubbleSwitchBtn->setButtonInfo("bubble.png", "bubble.png", "bubble.png", bubbleloc);
	this->addChild(_bubbleSwitchBtn, 2);

	auto circlepos = (Sprite *)(rootNode->getChildByName("circle"));
	Point circleloc = circlepos->getPosition();
	circlepos->setVisible(false);
	_circleSwitchBtn = CSwitchButton::create();
	_circleSwitchBtn->setButtonInfo("circle.png", "circle.png", "circle.png", circleloc);
	this->addChild(_circleSwitchBtn, 2);

	auto cloudpos = (Sprite *)(rootNode->getChildByName("cloud"));
	Point cloudloc = cloudpos->getPosition();
	cloudpos->setVisible(false);
	_cloudSwitchBtn = CSwitchButton::create();
	_cloudSwitchBtn->setButtonInfo("cloud.png", "cloud.png", "cloud.png", cloudloc);
	this->addChild(_cloudSwitchBtn, 2);

	auto cometpos = (Sprite *)(rootNode->getChildByName("comet"));
	Point cometloc = cometpos->getPosition();
	cometpos->setVisible(false);
	_cometSwitchBtn = CSwitchButton::create();
	_cometSwitchBtn->setButtonInfo("comet.png", "comet.png", "comet.png", cometloc);
	this->addChild(_cometSwitchBtn, 2);

	auto flarepos = (Sprite *)(rootNode->getChildByName("flare"));
	Point flareloc = flarepos->getPosition();
	flarepos->setVisible(false);
	_flareSwitchBtn = CSwitchButton::create();
	_flareSwitchBtn->setButtonInfo("flare.png", "flare.png", "flare.png", flareloc);
	this->addChild(_flareSwitchBtn, 2);

	auto raindroppos = (Sprite *)(rootNode->getChildByName("raindrop"));
	Point raindroploc = raindroppos->getPosition();
	raindroppos->setVisible(false);
	_raindropSwitchBtn = CSwitchButton::create();
	_raindropSwitchBtn->setButtonInfo("raindrop.png", "raindrop.png", "raindrop.png", raindroploc);
	this->addChild(_raindropSwitchBtn, 2);

	auto sparkpos = (Sprite *)(rootNode->getChildByName("spark"));
	Point sparkloc = sparkpos->getPosition();
	sparkpos->setVisible(false);
	_sparkSwitchBtn = CSwitchButton::create();
	_sparkSwitchBtn->setButtonInfo("spark.png", "spark.png", "spark.png", sparkloc);
	this->addChild(_sparkSwitchBtn, 2);

	// Particle Control System
	// 最好的方式是，以下的 Slider 根據這裡的設定值，顯示出正確的數值與位置
	_ParticleControl.init(*this);
	_ParticleControl._emitterPt = _EmitterSprite->getLoc(); // Emitter 目前的位置
	_ParticleControl._fDir = 90.0;
	_ParticleControl._iNumParticles = 100;
	_ParticleControl._iGenParticles = 0;
	_ParticleControl._fSpread = 180.0f;
	_ParticleControl._fVelocity = 2.5;	 // 分子的離開速度
	_ParticleControl._fLifeTime = 3.5f;	 // 分子的存活時間
	_ParticleControl._fSpin = 0;
	_ParticleControl._fGravity = 0;
	_ParticleControl._fElpasedTime = 0;
	_ParticleControl.setType(STAY_FOR_TWOSECONDS); // 分子運動的型態，預設為 0
	_ParticleControl._windDir = Point(0, 0); // 本範例沒有實作此項功能

	// 分子的可調整參數的捲動軸
	// Slider of Gravity
	auto *GravitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Gravity"));
	GravitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::GravityEvent, this));
	GravitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 -10 到 10 之間
	_GravityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("GravityBMFont");

	// Slider of Spread
	auto *SpreadSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Spread"));
	SpreadSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpreadEvent, this));
	SpreadSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 180 之間
	_SpreadBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpreadBMFont");

	// Slider of Direction
	auto *DirectionSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Direction"));
	DirectionSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::DirectionEvent, this));
	DirectionSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_DirectionBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("DirectionBMFont");

	// Slider of Spin
	auto *SpinSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Spin"));
	SpinSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpinEvent, this));
	SpinSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_SpinBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpinBMFont");

	// Slider of Opacity
	auto *OpacitySlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Opacity"));
	OpacitySlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::OpacityEvent, this));
	OpacitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_OpacityBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("OpacityBMFont");

	// Slider of Particles
	auto *ParticlesSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Particles"));
	ParticlesSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::ParticlesEvent, this));
	ParticlesSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_ParticlesBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("ParticlesBMFont");

	// Slider of Speed
	auto *SpeedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Speed"));
	SpeedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::SpeedEvent, this));
	SpeedSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_SpeedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("SpeedBMFont");

	// Slider of Lifetime
	auto *LifetimeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Lifetime"));
	LifetimeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::LifetimeEvent, this));
	LifetimeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_LifetimeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("LifetimeBMFont");

	// Slider of Red
	auto *RedSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Red"));
	RedSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::RedEvent, this));
	RedSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_RedBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("RedBMFont");

	// Slider of Green
	auto *GreenSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Green"));
	GreenSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::GreenEvent, this));
	GreenSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_GreenBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("GreenBMFont");

	// Slider of Blue
	auto *BlueSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Blue"));
	BlueSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::BlueEvent, this));
	BlueSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_BlueBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("BlueBMFont");

	// Slider of Wind
	auto *WindSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Wind"));
	WindSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::WindEvent, this));
	WindSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_WindBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("WindBMFont");

	//Particle Taki
	_particletaki = (ParticleSystem *)rootNode->getChildByName("Particle_Taki");
	_particletaki->setVisible(false);

	//Particle Snow
	_particlesnow = (ParticleSystem *)rootNode->getChildByName("Particle_Snow");
	_particlesnow->setVisible(false);

	//Particle Galaxy3
	_particlegalaxy3 = (ParticleSystem *)rootNode->getChildByName("Particle_galaxy3");
	_particlegalaxy3->setVisible(false);

	// Slider of Type
	auto *TypeSlider = (cocos2d::ui::Slider *)(rootNode->getChildByName("Slider_Type"));
	TypeSlider->addEventListener(CC_CALLBACK_2(ParticleSystemScene::TypeEvent, this));
	TypeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
	_TypeBMValue = (cocos2d::ui::TextBMFont *)rootNode->getChildByName("TypeBMFont");

	//button1 listener
	_cuberbtn = dynamic_cast<Button*>(rootNode->getChildByName("Button_1"));
	_cuberbtn->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::CuberBtnTouchEvent, this));

	//button2 listener
	_cuberbtn2 = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
	_cuberbtn2->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::CuberBtnTouchEvent2, this));

	//button3 listener
	_cuberbtn3 = dynamic_cast<Button*>(rootNode->getChildByName("Button_3"));
	_cuberbtn3->addTouchEventListener(CC_CALLBACK_2(ParticleSystemScene::CuberBtnTouchEvent3, this));

	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(ParticleSystemScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(ParticleSystemScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(ParticleSystemScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(ParticleSystemScene::doStep));

    return true;
}

void ParticleSystemScene::doStep(float dt)
{
	_ParticleControl.doStep(dt);

	//emitterEffect
	if (_bEmitter01On&&!_bEmitter02On&&!_bEmitter03On&&!_bEmitter04On) {
		_fEmitter01Time += dt;
		float t = 2.0f * M_PI * (_fEmitter01Time / 1.0f);
		float posx, posy;
		float r = 130*(cosf(2 * t) + sinf(2 * t));
		posx = r*cosf(t); posy = r*sinf(t);
		_EmitterSprite->setPosition(Point(posx, posy));
		if (_fEmitter01Time >= 1.0f)_fEmitter01Time = 0.0f;
		_ParticleControl._emitterPt = Point(500.0f+posx, 400.0f+posy);
		_ParticleControl._fLifeTime = 2.0f;
		_ParticleControl._fVelocity = 0.4f;
	}

	if (_bEmitter02On&&!_bEmitter01On&&!_bEmitter03On&&!_bEmitter04On) {
		_fEmitter02Time += dt;
		float t = 2.0f * M_PI * (_fEmitter02Time / 1.0f);
		float r = 100*sqrt(9 * cosf(2 * t));
		float posx, posy;
		posx = r*cosf(t); posy = r*sinf(t);
		_EmitterSprite->setPosition(Point(posx, posy));
		if (_fEmitter02Time >= 1.0f)_fEmitter02Time = 0.0f;
		_ParticleControl._emitterPt = Point(500.0f + posx, 500.0f + posy);
		_ParticleControl._fLifeTime = 2.5f;
		_ParticleControl._fVelocity = 0.2f;
	}

	if (_bEmitter03On&&!_bEmitter01On&&!_bEmitter02On&&!_bEmitter04On) {
		_fEmitter03Time += dt;
		float t = 2.0f * M_PI * (_fEmitter03Time / 1.0f);
		float r = 120*(2 * sinf(4 * t));
		float posx, posy;
		posx = r*cosf(t); posy = r*sinf(t);
		_EmitterSprite->setPosition(Point(posx, posy));
		if (_fEmitter03Time >= 1.0f)_fEmitter03Time = 0.0f;
		_ParticleControl._emitterPt = Point(550.0f + posx, 350.0f + posy);
		_ParticleControl._fLifeTime = 3.5f;
		_ParticleControl._fVelocity = 0.1f;
	}

	if (_bEmitter04On&&!_bEmitter01On&&!_bEmitter02On&&!_bEmitter03On) {
		_fEmitter04Time += dt;
		float t = 2.0f * M_PI * (_fEmitter04Time / 1.0f);
		float r = 100 ;
		float posx, posy;
		posx = r*cosf(t); posy = r*t-15;
		_EmitterSprite->setPosition(Point(0, -350.0f+ posy));
		if (_fEmitter04Time >= 1.2f)_fEmitter04Time = 0.0f;
		_ParticleControl._emitterPt = Point(500.0f, -200.0f+posy);
		_ParticleControl._fLifeTime = 1.0f;
		_ParticleControl._fVelocity = 0.1f;
		if (_ParticleControl._emitterPt.y>500)
		{
			_ParticleControl._fVelocity = 10.5f;
			_ParticleControl._fLifeTime = 0.9f;
			_ParticleControl._iGenParticles = 0;
		}
	}
	if (!_bEmitter01On&&!_bEmitter02On&&!_bEmitter03On&&!_bEmitter04On){
		_ParticleControl._emitterPt = _EmitterSprite->getLoc();
		_EmitterSprite->setPosition(Point(0, 0));
		//_ParticleControl._fVelocity = 2.5;	 // 分子的離開速度
		//_ParticleControl._fLifeTime = 3.5f;	 // 分子的存活時間
	}
}

bool ParticleSystemScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	//顯示 Emitter 時，可拖曳該圖式
	if( _bEmitterOn ) _EmitterSprite->touchesBegan(touchLoc);
	// 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
	//if ( !_emitterSwitchBtn->touchesBegan(touchLoc) && !_bEmitterOn ) _ParticleControl.onTouchesBegan(touchLoc);

	//只要這些按鈕沒被按在上面，就能顯示分子
	if ((!_emitterSwitchBtn->touchesBegan(touchLoc) &&
		!_bubbleSwitchBtn->touchesBegan(touchLoc) &&
		!_circleSwitchBtn->touchesBegan(touchLoc) &&
		!_cloudSwitchBtn->touchesBegan(touchLoc) &&
		!_cometSwitchBtn->touchesBegan(touchLoc) &&
		!_flareSwitchBtn->touchesBegan(touchLoc) &&
		!_raindropSwitchBtn->touchesBegan(touchLoc) &&
		!_sparkSwitchBtn->touchesBegan(touchLoc) &&
		!_emitter01SwitchBtn->touchesBegan(touchLoc) &&
		!_emitter02SwitchBtn->touchesBegan(touchLoc) &&
		!_emitter03SwitchBtn->touchesBegan(touchLoc) &&
		!_emitter04SwitchBtn->touchesBegan(touchLoc)
		) && !_bEmitterOn) _ParticleControl.onTouchesBegan(touchLoc);
	return true;
}

void  ParticleSystemScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();	
	if (_bEmitterOn) {
		if (_EmitterSprite->touchesMoved(touchLoc)) // 移動並更新 Emitter 的位置
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// 沒有顯示 Emitter，而且沒有按在 Emitter 切換按鈕上，才讓 touch 可以點選顯示分子
	//if ( !_emitterSwitchBtn->touchesMoved(touchLoc) && !_bEmitterOn ) _ParticleControl.onTouchesMoved(touchLoc);

	if ((!_emitterSwitchBtn->touchesMoved(touchLoc) &&
		!_bubbleSwitchBtn->touchesMoved(touchLoc) &&
		!_circleSwitchBtn->touchesMoved(touchLoc) &&
		!_cloudSwitchBtn->touchesMoved(touchLoc) &&
		!_cometSwitchBtn->touchesMoved(touchLoc) &&
		!_flareSwitchBtn->touchesMoved(touchLoc) &&
		!_raindropSwitchBtn->touchesMoved(touchLoc) &&
		!_sparkSwitchBtn->touchesMoved(touchLoc) &&
		!_emitter01SwitchBtn->touchesMoved(touchLoc) &&
		!_emitter02SwitchBtn->touchesMoved(touchLoc) &&
		!_emitter03SwitchBtn->touchesMoved(touchLoc) &&
		!_emitter04SwitchBtn->touchesMoved(touchLoc)
		) && !_bEmitterOn) _ParticleControl.onTouchesMoved(touchLoc);
}

void  ParticleSystemScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_bEmitterOn) {
		if( _EmitterSprite->touchesEnded(touchLoc) ) 
			_ParticleControl._emitterPt = _EmitterSprite->getLoc();
	}
	// 點在 Emitter 切換的圖示上，進行必要的狀態改變
	if (_emitterSwitchBtn->touchesEnded(touchLoc))
	{
		_bEmitterOn = _emitterSwitchBtn->getStatus();
		if ( _bEmitterOn ) { // 顯示 Emitter 圖示
			_EmitterSprite->setVisible(true);			
		}
		else { // 關閉 Emitter 圖示
			_EmitterSprite->setVisible(false);
		}
		_ParticleControl.setEmitter(_bEmitterOn); // 更新控制系統中的 Emitter 狀態
	}

	if (_bubbleSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setBubble(*this); // 更新控制系統中的 bubble 狀態
	if (_circleSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setCircle(*this); // 更新控制系統中的 circle 狀態
	if (_cloudSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setCloud(*this); // 更新控制系統中的 cloud 狀態
	if (_cometSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setComet(*this); // 更新控制系統中的 comet 狀態
	if (_flareSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setFlare(*this); // 更新控制系統中的 flare 狀態
	if (_raindropSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setRain(*this); // 更新控制系統中的 rain 狀態
	if (_sparkSwitchBtn->touchesEnded(touchLoc))_ParticleControl.setSpark(*this); // 更新控制系統中的 spark 狀態

	if (_emitter01SwitchBtn->touchesEnded(touchLoc))
	{
		if (_bEmitter01On)
		{
			_bEmitter01On = false;
			_fEmitter01Time = 0.0f;
		}
		else
		{
			_bEmitter01On = true;
		}
	}

	if (_emitter02SwitchBtn->touchesEnded(touchLoc))
	{
		if (_bEmitter02On)
		{
			_bEmitter02On = false;
			_fEmitter02Time = 0.0f;
		}
		else
		{
			_bEmitter02On = true;
		}
	}

	if (_emitter03SwitchBtn->touchesEnded(touchLoc))
	{
		if (_bEmitter03On)
		{
			_bEmitter03On = false;
			_fEmitter03Time = 0.0f;
		}
		else
		{
			_bEmitter03On = true;
		}
	}

	if (_emitter04SwitchBtn->touchesEnded(touchLoc))
	{
		if (_bEmitter04On)
		{
			_bEmitter04On = false;
			_fEmitter04Time = 0.0f;
		}
		else
		{
			_bEmitter04On = true;
		}
	}
}

void ParticleSystemScene::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		float fGravity = (-50.0f + percent) / 5.0f;
		_GravityBMValue->setString(StringUtils::format("%2.1f", fGravity));
		_ParticleControl.setGravity(fGravity);
	}
}

void ParticleSystemScene::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpread = percent*1.8f; // 0 到 180 之間
		_SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
		_ParticleControl._fSpread = fSpread;
	}
}

void ParticleSystemScene::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fDir = percent*3.6f; // 0 到 360 之間
		_DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
		_ParticleControl._fDir = fDir;
	}
}

void ParticleSystemScene::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpin = percent *1.8; // 0 到 180 之間
		_SpinBMValue->setString(StringUtils::format("%2.1f", fSpin));
		//_ParticleControl.setSpin(fSpin);
		_ParticleControl._fSpin = fSpin;
	}
}

void ParticleSystemScene::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fOpacity = percent*2.55f; // 0 到 255 之間
		_OpacityBMValue->setString(StringUtils::format("%2.1f", fOpacity));
		_ParticleControl.setOpacity(fOpacity);
		//_ParticleControl._fOpacity = fOpacity;
	}
}

void ParticleSystemScene::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		int iParticles = percent*2.0f; // 0 到 255 之間
		_ParticlesBMValue->setString(StringUtils::format("%2d", iParticles));
		_ParticleControl.setNumParticles(iParticles);
	}
}

void ParticleSystemScene::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fSpeed = percent/2.5f; // 0 到 40 之間
		_SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
		_ParticleControl.setSpeed(fSpeed);
		//_ParticleControl._fVelocity = fSpeed;
	}
}

void ParticleSystemScene::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fLifetime = percent*0.07f; // 0 到 360 之間
		_LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
		_ParticleControl._fLifeTime = fLifetime;
	}
}

void ParticleSystemScene::RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fRed = percent*2.55f; // 0 到 255 之間
		_RedBMValue->setString(StringUtils::format("%2.1f", fRed));
		_ParticleControl._color.r = fRed;
	}
}

void ParticleSystemScene::GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fGreen = percent*2.55f; // 0 到 255 之間
		_GreenBMValue->setString(StringUtils::format("%2.1f", fGreen));
		_ParticleControl._color.g = fGreen;
	}
}

void ParticleSystemScene::BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fBlue = percent*2.55f; // 0 到 255 之間
		_BlueBMValue->setString(StringUtils::format("%2.1f", fBlue));
		_ParticleControl._color.b = fBlue;
	}
}

void ParticleSystemScene::WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		float fWind = (-50.0f + percent) / 10.0f; // -10 到 10 之間
		_WindBMValue->setString(StringUtils::format("%2.1f", fWind));
		_ParticleControl.setWind(fWind);
	}
}


void ParticleSystemScene::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		int iType = percent*0.08; // 0 到 360 之間
		_TypeBMValue->setString(StringUtils::format("%2d", iType));
		_ParticleControl.setType(iType);
	}
}

void ParticleSystemScene::CuberBtnTouchEvent(Ref *pSender, cocos2d::ui::Button::TouchEventType type)
{
	Point buttontouch = _cuberbtn->getPosition();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		
		buttontouch.y = 500.0f;
		_ParticleControl.setType(99);
		_ParticleControl.onTouchesBegan(buttontouch);
		_cuberbtn->setScale(1);
		log("Touch Down");
		break;
	case Widget::TouchEventType::MOVED:
		log("Touch Move");
		_cuberbtn->setScale(1.25f);
		break;
	case Widget::TouchEventType::ENDED:
		_cuberbtn->setScale(1);
		if (!_bcuberbtn) {
			_bcuberbtn = true;
			_particlegalaxy3->setVisible(true);
			_bcuberbtn2 = false;
			_particlesnow->setVisible(false);
			_bcuberbtn3 = false;
			_particletaki->setVisible(false);
		}
		else {
			_bcuberbtn = false;
			_particlegalaxy3->setVisible(false);
		}
		log("Touch Up");
		break;
	case Widget::TouchEventType::CANCELED:
		log("Touch Cancelled");
		break;
	default:
		break;
	}
}

void ParticleSystemScene::CuberBtnTouchEvent2(Ref *pSender, cocos2d::ui::Button::TouchEventType type)
{
	Point buttontouch = _cuberbtn2->getPosition();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		buttontouch.y = 300.0f;
		_ParticleControl.setType(99);
		_ParticleControl.onTouchesBegan(buttontouch);
		_cuberbtn2->setScale(1);
		log("Touch Down");
		break;
	case Widget::TouchEventType::MOVED:
		log("Touch Move");
		_cuberbtn2->setScale(1.25f);
		break;
	case Widget::TouchEventType::ENDED:
		log("Touch Up");
		_cuberbtn2->setScale(1);
		if (!_bcuberbtn2) {
			_bcuberbtn2 = true;
			_particlesnow->setVisible(true);
			_bcuberbtn = false;
			_particlegalaxy3->setVisible(false);
			_bcuberbtn3 = false;
			_particletaki->setVisible(false);
		}
		else {
			_bcuberbtn2 = false;
			_particlesnow->setVisible(false);
		}
		break;
	case Widget::TouchEventType::CANCELED:
		log("Touch Cancelled");
		break;
	default:
		break;
	}
}

void ParticleSystemScene::CuberBtnTouchEvent3(Ref *pSender, cocos2d::ui::Button::TouchEventType type)
{
	Point buttontouch = _cuberbtn3->getPosition();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		buttontouch.y = 600.0f;
		_ParticleControl.setType(99);
		_ParticleControl.onTouchesBegan(buttontouch);
		_cuberbtn3->setScale(1);
		log("Touch Down");
		break;
	case Widget::TouchEventType::MOVED:
		log("Touch Move");
		_cuberbtn3->setScale(1.25f);
		break;
	case Widget::TouchEventType::ENDED:
		log("Touch Up");
		_cuberbtn3->setScale(1);
		if (!_bcuberbtn3) {
			_bcuberbtn3 = true;
			_particletaki->setVisible(true);
			_bcuberbtn = false;
			_particlegalaxy3->setVisible(false);
			_bcuberbtn2 = false;
			_particlesnow->setVisible(false);
		}
		else {
			_bcuberbtn3 = false;
			_particletaki->setVisible(false);
		}
		break;
	case Widget::TouchEventType::CANCELED:
		log("Touch Cancelled");
		break;
	default:
		break;
	}
}

//if (_bEmitter01On&&!_bEmitter02On&&!_bEmitter03On) {
//	_fEmitter01Time += dt;
//	float t = 2.0f * M_PI * (_fEmitter01Time / 1.0f);
//	float sint = sinf(t);
//	float cost = cosf(t);
//	float  cos2t, cos3t, cos4t, sin12t;
//	cos2t = cosf(2 * t); cos3t = cosf(3 * t); cos4t = cosf(4 * t);
//	sin12t = sin(t / 12.0f);
//	//_EmitterSprite->setPosition(Point(200.0f , 200.0f));
//	float posx, posy;
//	posx = 15 * (16 * sint*sint*sint); posy = 15 * (13 * cost - 5 * cos2t - 2 * cos3t - cos4t);
//	_EmitterSprite->setPosition(Point(posx, posy));
//	//_EmitterSprite->setPosition(Point(15 * (16 * sint*sint*sint), 15 * (13 * cost - 5 * cos2t - 2 * cos3t - cos4t)));
//	if (_fEmitter01Time >= 1.0f)_fEmitter01Time = 0.0f;
//	_ParticleControl._emitterPt = Point(500.0f + posx, 400.0f + posy);
//	_ParticleControl._fLifeTime = 1.0f;
//	_ParticleControl._fVelocity = 0.4f;
//}