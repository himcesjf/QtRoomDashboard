#include "SensorModel.h"
#include <spdlog/spdlog.h>
#include <QDateTime>

SensorModel::SensorModel(QObject *parent)
    : QObject(parent)
    , m_temperature(20.0)
    , m_humidity(50.0)
    , m_co2(400.0)
    , m_recording(false)
{
    connect(&m_worker, &SensorWorker::sensorDataChanged,
            this, &SensorModel::onSensorDataChanged);
    m_worker.start();
}

SensorModel::~SensorModel() {
    if (m_recording) {
        stopRecording();
    }
    m_worker.stop();
}

void SensorModel::onSensorDataChanged(double temperature, double humidity, double co2) {
    setTemperature(temperature);
    setHumidity(humidity);
    setCo2(co2);
}

void SensorModel::setTemperature(double temp) {
    if (m_temperature != temp) {
        m_temperature = temp;
        emit temperatureChanged();
        
        if (m_recording && m_csvWriter) {
            m_csvWriter->writeRow({
                QString::number(temp).toStdString(),
                QString::number(m_humidity).toStdString(),
                QString::number(m_co2).toStdString(),
                QDateTime::currentDateTime().toString(Qt::ISODate).toStdString()
            });
        }
    }
}

void SensorModel::setHumidity(double hum) {
    if (m_humidity != hum) {
        m_humidity = hum;
        emit humidityChanged();
    }
}

void SensorModel::setCo2(double co2) {
    if (m_co2 != co2) {
        m_co2 = co2;
        emit co2Changed();
    }
}

void SensorModel::setRecording(bool recording) {
    if (recording != m_recording) {
        if (recording) {
            startRecording();
        } else {
            stopRecording();
        }
    }
}

void SensorModel::startRecording() {
    if (!m_recording) {
        QString filename = QString("sensor_data_%1.csv")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"));
        m_csvWriter = std::make_unique<CsvWriter>(filename.toStdString());
        
        if (m_csvWriter->isOpen()) {
            m_csvWriter->writeHeader({"Temperature", "Humidity", "CO2", "Timestamp"});
            m_recording = true;
            emit recordingChanged();
            spdlog::info("Started recording to {}", filename.toStdString());
        } else {
            m_csvWriter.reset();
            spdlog::error("Failed to start recording");
        }
    }
}

void SensorModel::stopRecording() {
    if (m_recording) {
        m_csvWriter.reset();
        m_recording = false;
        emit recordingChanged();
        spdlog::info("Stopped recording");
    }
}