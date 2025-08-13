/*!
 *  @file scpi_rp_gen.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "scpi/scpi_rp_gen.h"

#include "common/base_io.h"
#include "gen/gen.h"
#include "gen/gen_burst.h"
#include "gen/gen_settings.h"
#include "gen/gen_sweep.h"
#include "gen/gen_trig.h"

using namespace scpi_rp;

void SCPIGen::setInterface(BaseIO *io) { m_io = io; }

bool SCPIGen::reset() {
  if (m_io == nullptr) return false;
  return setGenReset(m_io);
}

bool SCPIGen::sync() {
  if (m_io == nullptr) return false;
  return setGenSync(m_io);
}

bool SCPIGen::sync(EGENChannel channel) {
  if (m_io == nullptr) return false;
  return setGenTrig(m_io, channel);
}

bool SCPIGen::enable(EGENChannel channel, bool state) {
  if (m_io == nullptr) return false;
  return setGenEnable(m_io, channel, state);
}

bool SCPIGen::enableSync(bool state) {
  if (m_io == nullptr) return false;
  return setGenEnableSync(m_io, state);
}

bool SCPIGen::enableQ(EGENChannel channel, bool *state) {
  if (m_io == nullptr) return false;
  return getGenEnable(m_io, channel, state);
}

bool SCPIGen::trigSource(EGENChannel channel, EGENTrigger mode) {
  if (m_io == nullptr) return false;
  return setGenTrigSource(m_io, channel, mode);
}

bool SCPIGen::trigSourceQ(EGENChannel channel, EGENTrigger *mode) {
  if (m_io == nullptr) return false;
  return getGenTrigSource(m_io, channel, mode);
}

bool SCPIGen::trigExtDebouncer(int uSec) {
  if (m_io == nullptr) return false;
  return setGenExtTrigDebouncer(m_io, uSec);
}

bool SCPIGen::trigExtDebouncerQ(int *uSec) {
  if (m_io == nullptr) return false;
  return getGenExtTrigDebouncer(m_io, uSec);
}

bool SCPIGen::trigExtLevel(float level) {
  if (m_io == nullptr) return false;
  return setGenExtTrigLevel(m_io, level);
}

bool SCPIGen::trigExtLevelQ(float *level) {
  if (m_io == nullptr) return false;
  return getGenExtTrigLevel(m_io, level);
}

bool SCPIGen::wave(EGENChannel channel, EGENWave wave) {
  if (m_io == nullptr) return false;
  return setGenFunc(m_io, channel, wave);
}

bool SCPIGen::waveQ(EGENChannel channel, EGENWave *wave) {
  if (m_io == nullptr) return false;
  return getGenFunc(m_io, channel, wave);
}

bool SCPIGen::freq(EGENChannel channel, float freq) {
  if (m_io == nullptr) return false;
  return setGenFreq(m_io, channel, freq);
}

bool SCPIGen::freqDirect(EGENChannel channel, float freq) {
  if (m_io == nullptr) return false;
  return setGenFreqDirect(m_io, channel, freq);
}

bool SCPIGen::freqQ(EGENChannel channel, float *freq) {
  if (m_io == nullptr) return false;
  return getGenFreq(m_io, channel, freq);
}

bool SCPIGen::amp(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenAmp(m_io, channel, value);
}

bool SCPIGen::ampQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenAmp(m_io, channel, value);
}

bool SCPIGen::offset(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenOffset(m_io, channel, value);
}

bool SCPIGen::offsetQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenOffset(m_io, channel, value);
}

bool SCPIGen::phase(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenPhase(m_io, channel, value);
}

bool SCPIGen::phaseQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenPhase(m_io, channel, value);
}

bool SCPIGen::dutyCycle(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenDCYC(m_io, channel, value);
}

bool SCPIGen::dutyCycleQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenDCYC(m_io, channel, value);
}

bool SCPIGen::load(EGENChannel channel, EGENLoad load) {
  if (m_io == nullptr) return false;
  return setGenLoad(m_io, channel, load);
}

bool SCPIGen::loadQ(EGENChannel channel, EGENLoad *load) {
  if (m_io == nullptr) return false;
  return getGenLoad(m_io, channel, load);
}

bool SCPIGen::arbWave(EGENChannel channel, float value, bool last) {
  if (m_io == nullptr) return false;
  return setGenARBData(m_io, channel, value, last);
}

bool SCPIGen::arbWaveQ(EGENChannel channel, float *value, bool *last) {
  if (m_io == nullptr) return false;
  return getGenARBData(m_io, channel, value, last);
}

bool SCPIGen::initValue(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenInitValue(m_io, channel, value);
}

bool SCPIGen::initValueQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenInitValue(m_io, channel, value);
}

bool SCPIGen::genMode(EGENChannel channel, EGENBurst mode) {
  if (m_io == nullptr) return false;
  return setGenBurstMode(m_io, channel, mode);
}

bool SCPIGen::genModeQ(EGENChannel channel, EGENBurst *mode) {
  if (m_io == nullptr) return false;
  return getGenBurstMode(m_io, channel, mode);
}

bool SCPIGen::burstInitValue(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenBurstInitValue(m_io, channel, value);
}

bool SCPIGen::burstInitValueQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenBurstInitValue(m_io, channel, value);
}

bool SCPIGen::burstLastValue(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenBurstLastValue(m_io, channel, value);
}

bool SCPIGen::burstLastValueQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenBurstLastValue(m_io, channel, value);
}

bool SCPIGen::burstNCycles(EGENChannel channel, uint16_t value) {
  if (m_io == nullptr) return false;
  return setGenBurstNCyc(m_io, channel, value);
}

bool SCPIGen::burstNCyclesQ(EGENChannel channel, uint16_t *value) {
  if (m_io == nullptr) return false;
  return getGenBurstNCyc(m_io, channel, value);
}

bool SCPIGen::burstNRepetitions(EGENChannel channel, uint16_t value) {
  if (m_io == nullptr) return false;
  return setGenBurstNRep(m_io, channel, value);
}

bool SCPIGen::burstNRepetitionsQ(EGENChannel channel, uint16_t *value) {
  if (m_io == nullptr) return false;
  return getGenBurstNRep(m_io, channel, value);
}

bool SCPIGen::burstPeriod(EGENChannel channel, uint32_t value) {
  if (m_io == nullptr) return false;
  return setGenBurstPeriod(m_io, channel, value);
}

bool SCPIGen::burstPeriodQ(EGENChannel channel, uint32_t *value) {
  if (m_io == nullptr) return false;
  return getGenBurstPeriod(m_io, channel, value);
}

bool SCPIGen::sweepDefault() {
  if (m_io == nullptr) return false;
  return setGenSweepDefault(m_io);
}

bool SCPIGen::sweepReset() {
  if (m_io == nullptr) return false;
  return setGenSweepReset(m_io);
}

bool SCPIGen::sweepPause(bool stop) {
  if (m_io == nullptr) return false;
  return setGenSweepPause(m_io, stop);
}

bool SCPIGen::sweepState(EGENChannel channel, bool state) {
  if (m_io == nullptr) return false;
  return setGenSweepState(m_io, channel, state);
}

bool SCPIGen::sweepStateQ(EGENChannel channel, bool *state) {
  if (m_io == nullptr) return false;
  return getGenSweepState(m_io, channel, state);
}

bool SCPIGen::sweepFreqStart(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenSweepFreqStart(m_io, channel, value);
}

bool SCPIGen::sweepFreqStartQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenSweepFreqStart(m_io, channel, value);
}

bool SCPIGen::sweepFreqEnd(EGENChannel channel, float value) {
  if (m_io == nullptr) return false;
  return setGenSweepFreqStop(m_io, channel, value);
}

bool SCPIGen::sweepFreqEndQ(EGENChannel channel, float *value) {
  if (m_io == nullptr) return false;
  return getGenSweepFreqStop(m_io, channel, value);
}

bool SCPIGen::sweepTime(EGENChannel channel, uint64_t value) {
  if (m_io == nullptr) return false;
  return setGenSweepTime(m_io, channel, value);
}

bool SCPIGen::sweepTimeQ(EGENChannel channel, uint64_t *value) {
  if (m_io == nullptr) return false;
  return getGenSweepTime(m_io, channel, value);
}

bool SCPIGen::sweepMode(EGENChannel channel, EGENSweepMode mode) {
  if (m_io == nullptr) return false;
  return setGenSweepMode(m_io, channel, mode);
}

bool SCPIGen::sweepModeQ(EGENChannel channel, EGENSweepMode *mode) {
  if (m_io == nullptr) return false;
  return getGenSweepMode(m_io, channel, mode);
}

bool SCPIGen::sweepDirection(EGENChannel channel, EGENSweepDir mode) {
  if (m_io == nullptr) return false;
  return setGenSweepDir(m_io, channel, mode);
}

bool SCPIGen::sweepDirectionQ(EGENChannel channel, EGENSweepDir *mode) {
  if (m_io == nullptr) return false;
  return getGenSweepDir(m_io, channel, mode);
}