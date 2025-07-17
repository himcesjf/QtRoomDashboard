#pragma once

#include <QObject>
#include <QDateTime>
#include <memory>
#include "CsvWriter.h"
#include "SensorWorker.h"

class SensorModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(double temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(double humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
    Q_PROPERTY(double co2 READ co2 WRITE setCo2 NOTIFY co2Changed)
    Q_PROPERTY(bool recording READ recording WRITE setRecording NOTIFY recordingChanged)

public:
    explicit SensorModel(QObject *parent = nullptr);
    ~SensorModel();

    double temperature() const { return m_temperature; }
    double humidity() const { return m_humidity; }
    double co2() const { return m_co2; }
    bool recording() const { return m_recording; }

public slots:
    void setTemperature(double temp);
    void setHumidity(double hum);
    void setCo2(double co2);
    void setRecording(bool recording);
    void startRecording();
    void stopRecording();

private slots:
    void onSensorDataChanged(double temperature, double humidity, double co2);

signals:
    void temperatureChanged();
    void humidityChanged();
    void co2Changed();
    void recordingChanged();

private:
    double m_temperature;
    double m_humidity;
    double m_co2;
    bool m_recording;
    std::unique_ptr<CsvWriter> m_csvWriter;
    SensorWorker m_worker;
}; 