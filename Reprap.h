/****************************************************************************************************

RepRapFirmware - Reprap

RepRap is a simple class that acts as a container for an instance of all the others.

-----------------------------------------------------------------------------------------------------

Version 0.1

21 May 2013

Adrian Bowyer
RepRap Professional Ltd
http://reprappro.com

Licence: GPL

****************************************************************************************************/

#ifndef REPRAP_H
#define REPRAP_H

class RepRap
{    
  public:
      
    RepRap();
    void EmergencyStop();
    void Init();
    void Spin();
    void Exit();
    void Interrupt();
    void Diagnostics();
    void Timing();
    bool Debug() const;
    void SetDebug(bool d);
    void AddTool(Tool* t);
    void SelectTool(int toolNumber);
    void StandbyTool(int toolNumber);
    Tool* GetCurrentTool();
    Tool* GetTool(int toolNumber);
    void SetToolVariables(int toolNumber, float* standbyTemperatures, float* activeTemperatures);
    void AllowColdExtrude();
    void DenyColdExtrude();
    bool ColdExtrude() const;
    void PrintTool(int toolNumber, StringRef& reply) const;
    void FlagTemperatureFault(int8_t dudHeater);
    void ClearTemperatureFault(int8_t wasDudHeater);
    Platform* GetPlatform() const;
    Move* GetMove() const;
    Heat* GetHeat() const;
    GCodes* GetGCodes() const;
    Network* GetNetwork() const;
    Webserver* GetWebserver() const;
    void Tick();
    bool IsStopped() const;
    uint16_t GetTicksInSpinState() const;
    uint16_t GetExtrudersInUse() const;
    uint16_t GetHeatersInUse() const;
    
  private:
  
    Platform* platform;
    Network* network;
    Move* move;
    Heat* heat;
    GCodes* gCodes;
    Webserver* webserver;
    Tool* toolList;
    Tool* currentTool;
    uint16_t ticksInSpinState;
    uint8_t spinState;
    bool debug;
    float fastLoop, slowLoop;
    float lastTime;
    bool stopped;
    bool active;
    bool resetting;
    uint16_t activeExtruders;
    uint16_t activeHeaters;
    bool coldExtrude;
};

inline Platform* RepRap::GetPlatform() const { return platform; }
inline Move* RepRap::GetMove() const { return move; }
inline Heat* RepRap::GetHeat() const { return heat; }
inline GCodes* RepRap::GetGCodes() const { return gCodes; }
inline Network* RepRap::GetNetwork() const { return network; }
inline Webserver* RepRap::GetWebserver() const { return webserver; }
inline bool RepRap::Debug() const { return debug; }
inline Tool* RepRap::GetCurrentTool() { return currentTool; }
inline uint16_t RepRap::GetExtrudersInUse() const { return activeExtruders; }
inline uint16_t RepRap::GetHeatersInUse() const { return activeHeaters; }
inline bool RepRap::ColdExtrude() const { return coldExtrude; }
inline void RepRap::AllowColdExtrude() { coldExtrude = true; }
inline void RepRap::DenyColdExtrude() { coldExtrude = false; }

inline void RepRap::FlagTemperatureFault(int8_t dudHeater)
{
	if(toolList != NULL)
	{
		toolList->FlagTemperatureFault(dudHeater);
	}
}

inline void RepRap::ClearTemperatureFault(int8_t wasDudHeater)
{
	reprap.GetHeat()->ResetFault(wasDudHeater);
	if(toolList != NULL)
	{
		toolList->ClearTemperatureFault(wasDudHeater);
	}
}

inline void RepRap::SetDebug(bool d)
{
	debug = d;
	if(debug)
	{
		platform->Message(BOTH_MESSAGE, "Debugging enabled\n");
	}
	else
	{
		platform->Message(WEB_MESSAGE, "");
	}
}

inline void RepRap::Interrupt() { move->Interrupt(); }
inline bool RepRap::IsStopped() const { return stopped; }
inline uint16_t RepRap::GetTicksInSpinState() const { return ticksInSpinState; }

#endif


