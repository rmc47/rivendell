// audio_convert_test.cpp
//
// Test the Rivendell file format converter.
//
//   (C) Copyright 2010-2016 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <rdapplication.h>
#include <rddb.h>
#include <rdcmd_switch.h>
#include <rdaudioconvert.h>

#include <QCoreApplication>

#include <audio_convert_test.h>

MainObject::MainObject(QObject *parent)
  :QObject(parent)
{
  new RDApplication(RDApplication::Console,"audio_convert_test",
		    AUDIO_CONVERT_TEST_USAGE);

  destination_settings=new RDSettings();
  start_point=-1;
  end_point=-1;
  speed_ratio=1.0;
  bool ok=false;
  RDAudioConvert::ErrorCode conv_err;

  //
  // Read Command Options
  //
  for(unsigned i=0;i<rda->cmdSwitch()->keys();i++) {
    if(rda->cmdSwitch()->key(i)=="--source-file") {
      source_filename=rda->cmdSwitch()->value(i);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--destination-file") {
      destination_filename=rda->cmdSwitch()->value(i);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--start-point") {
      start_point=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid start point\n");
	exit(256);
      }
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--end-point") {
      end_point=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid end point\n");
	exit(256);
      }
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--destination-format") {
      RDSettings::Format format=(RDSettings::Format)rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid destination format\n");
	exit(256);
      }
      switch(format) {
      case RDSettings::Pcm16:
      case RDSettings::Pcm24:
      case RDSettings::MpegL2:
      case RDSettings::MpegL2Wav:
      case RDSettings::MpegL3:
      case RDSettings::Flac:
      case RDSettings::OggVorbis:
	destination_settings->setFormat(format);
	rda->cmdSwitch()->setProcessed(i,true);
	break;

      default:
	fprintf(stderr,"audio_convert_test: invalid destination format\n");
	exit(256);
      }
      destination_settings->setFormat(format);
    }
    if(rda->cmdSwitch()->key(i)=="--destination-channels") {
      unsigned channels=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid destination channels\n");
	exit(256);
      }
      destination_settings->setChannels(channels);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--destination-sample-rate") {
      unsigned sample_rate=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid destination sample rate\n");
	exit(256);
      }
      destination_settings->setSampleRate(sample_rate);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--destination-bit-rate") {
      unsigned bit_rate=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid destination bit rate\n");
	exit(256);
      }
      destination_settings->setBitRate(bit_rate);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--quality") {
      unsigned quality=rda->cmdSwitch()->value(i).toInt(&ok);
      if(!ok) {
	fprintf(stderr,"audio_convert_test: invalid destination quality\n");
	exit(256);
      }
      destination_settings->setQuality(quality);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--normalization-level") {
      int normalization_level=rda->cmdSwitch()->value(i).toInt(&ok);
      if((!ok)||(normalization_level>0)) {
	fprintf(stderr,"audio_convert_test: invalid normalization level\n");
	exit(256);
      }
      destination_settings->setNormalizationLevel(normalization_level);
      rda->cmdSwitch()->setProcessed(i,true);
    }
    if(rda->cmdSwitch()->key(i)=="--speed-ratio") {
      speed_ratio=rda->cmdSwitch()->value(i).toFloat(&ok);
      if((!ok)||(speed_ratio<=0)) {
	fprintf(stderr,"audio_convert_test: invalid speed-ratio\n");
	exit(256);
      }
      rda->cmdSwitch()->setProcessed(i,true);
    }
  }
  if(source_filename.isEmpty()) {
    fprintf(stderr,"audio_convert_test: missing source-file\n");
    exit(256);
  }
  if(destination_filename.isEmpty()) {
    fprintf(stderr,"audio_convert_test: missing destination-file\n");
    exit(256);
  }
  if((destination_settings->bitRate()!=0)&&
     (destination_settings->quality()!=0)) {
    fprintf(stderr,"audio_convert_test: --destination-bit-rate and --destination-quality are mutually exclusive\n");
    exit(256);
  }

  RDAudioConvert *conv=new RDAudioConvert(rda->config()->stationName(),this);
  conv->setSourceFile(source_filename);
  conv->setDestinationFile(destination_filename);
  conv->setDestinationSettings(destination_settings);
  conv->setRange(start_point,end_point);
  conv->setSpeedRatio(speed_ratio);
  printf("Converting...\n");
  conv_err=conv->convert();
  printf("Result: %s\n",(const char *)RDAudioConvert::errorText(conv_err));
  delete conv;

  exit(0);
}


int main(int argc,char *argv[])
{
  QCoreApplication a(argc,argv);
  new MainObject();
  return a.exec();
}
