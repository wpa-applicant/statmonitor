# statmonitor

Sampling: 1/s  
DUT states: idle, fault, resetting, operational  
Events: pic-fault, pic-recovering, pic-recovered, pic-reset-start, pic-reset-done, adc-fault, adc-recovering, adc-recovered, adc-reset-start, adc-reset-done  

-- provided --  
We have a webserver which simulates DUTs by randomly changing states.  
After switching to fault state, the DUT can recover and go back to operational state.  
\---------------

-- assignment --  
Read config file  
Keep the last x DebugInfo objects in ring buffer.  
When error detected: (state changes to fault)  
  - Create new logfile
  - Log state transition event
  - Paste ring buffer to it  
  - Keep logging until recovered (state changed to operational)  
  - If recovery time expired, reset the DUT
  - Clear ring buffer
  - Keep logging until recovered  
  - Log state transition event

Clean up log files when neccessary  

\---------------
