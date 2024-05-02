//
// Created by loumtechnologies on 4/23/2024.
//

#include "Connection.h"
#include <print>
#include <QJsonArray>
#include <QJsonDocument>

#include "smp_bluetooth.h"
#include "smp_group_settings_mgmt.h"
#include "smp_group_shell_mgmt.h"
#include "smp_group_stat_mgmt.h"
#include "smp_group_zephyr_mgmt.h"
#include "smp_processor.h"
#include "CommonParameters.h"
#include "API.h"

enum mcumgr_action_t {
    ACTION_IDLE,

    ACTION_IMG_UPLOAD,
    ACTION_IMG_UPLOAD_SET,
    ACTION_OS_UPLOAD_RESET,
    ACTION_IMG_IMAGE_LIST,
    ACTION_IMG_IMAGE_SET,
    ACTION_IMG_IMAGE_ERASE,

    ACTION_OS_ECHO,
    ACTION_OS_TASK_STATS,
    ACTION_OS_MEMORY_POOL,
    ACTION_OS_RESET,
    ACTION_OS_DATETIME_GET,
    ACTION_OS_DATETIME_SET,
    ACTION_OS_MCUMGR_BUFFER,
    ACTION_OS_OS_APPLICATION_INFO,
    ACTION_OS_BOOTLOADER_INFO,

    ACTION_SHELL_EXECUTE,

    ACTION_STAT_GROUP_DATA,
    ACTION_STAT_LIST_GROUPS,

    ACTION_FS_UPLOAD,
    ACTION_FS_DOWNLOAD,
    ACTION_FS_STATUS,
    ACTION_FS_HASH_CHECKSUM,
    ACTION_FS_SUPPORTED_HASHES_CHECKSUMS,

    ACTION_SETTINGS_READ,
    ACTION_SETTINGS_WRITE,
    ACTION_SETTINGS_DELETE,
    ACTION_SETTINGS_COMMIT,
    ACTION_SETTINGS_LOAD,
    ACTION_SETTINGS_SAVE,

    ACTION_ZEPHYR_STORAGE_ERASE,
};

Connection::Connection(QBluetoothDeviceInfo *info, QObject *parent) : QObject(parent) {
    // controller = QLowEnergyController::createCentral(*info);
    // //controller->setParent(this);
    //
    // connect(controller, SIGNAL(connected()), this, SLOT(connected()));
    // connect(controller, SIGNAL(disconnected()), this, SLOT(disconnected()));
    // connect(controller, SIGNAL(discoveryFinished()), this, SLOT(discoveryFinished()));
    // connect(controller, SIGNAL(serviceDiscovered(QBluetoothUuid)), this, SLOT(serviceDiscovered(QBluetoothUuid)));
    // connect(controller, SIGNAL(error(QLowEnergyController::Error)), this, SLOT(errorz(QLowEnergyController::Error)));
    //
    // controller->setRemoteAddressType(QLowEnergyController::RandomAddress);
    // controller->connectToDevice();

    auto bluetooth_transport = new smp_bluetooth(parent);
    transport = bluetooth_transport;

    processor = new smp_processor(parent);
    processor->set_transport(transport);
    smp_groups = new smp_group_array();
    smp_groups->fs_mgmt = new smp_group_fs_mgmt(processor);
    smp_groups->img_mgmt = new smp_group_img_mgmt(processor);
    smp_groups->os_mgmt = new smp_group_os_mgmt(processor);
    smp_groups->settings_mgmt = new smp_group_settings_mgmt(processor);
    smp_groups->shell_mgmt = new smp_group_shell_mgmt(processor);
    smp_groups->stat_mgmt = new smp_group_stat_mgmt(processor);
    smp_groups->zephyr_mgmt = new smp_group_zephyr_mgmt(processor);

    bluetooth_transport->form_connect_to_device(*info);

    connect(bluetooth_transport, SIGNAL(receive_waiting(smp_message*)), processor, SLOT(message_received(smp_message*)));
    connect(smp_groups->fs_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->fs_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->img_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->img_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->img_mgmt, SIGNAL(plugin_to_hex(QByteArray*)), this, SLOT(group_to_hex(QByteArray*)));
    connect(smp_groups->os_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->os_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->settings_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->settings_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->shell_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->shell_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->stat_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->stat_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    connect(smp_groups->zephyr_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    connect(smp_groups->zephyr_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
}

Connection::~Connection() {
    auto bluetooth_transport = (smp_bluetooth*)transport;
    disconnect(bluetooth_transport, SIGNAL(receive_waiting(smp_message*)), processor, SLOT(message_received(smp_message*)));

    disconnect(smp_groups->fs_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->fs_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->img_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->img_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->img_mgmt, SIGNAL(plugin_to_hex(QByteArray*)), this, SLOT(group_to_hex(QByteArray*)));
    disconnect(smp_groups->os_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->os_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->settings_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->settings_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->shell_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->shell_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->stat_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->stat_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));
    disconnect(smp_groups->zephyr_mgmt, SIGNAL(status(uint8_t,group_status,QString)), this, SLOT(status(uint8_t,group_status,QString)));
    disconnect(smp_groups->zephyr_mgmt, SIGNAL(progress(uint8_t,uint8_t)), this, SLOT(progress(uint8_t,uint8_t)));

    isDeleting = true;
    delete smp_groups->fs_mgmt;
    delete smp_groups->img_mgmt;
    delete smp_groups->os_mgmt;
    delete smp_groups->settings_mgmt;
    delete smp_groups->shell_mgmt;
    delete smp_groups->stat_mgmt;
    delete smp_groups->zephyr_mgmt;
    delete smp_groups;
    delete processor;
    delete transport;
}

void Connection::reset(bool force) {
    smp_groups->os_mgmt->start_reset(force);
}

void Connection::imageUpload(int image, QString fileName, bool upgrade, CommonParameters &parameters) {
    smp_groups->img_mgmt->set_parameters(parameters.getProtocolVersion(), parameters.getMtu(), parameters.getRetries(), parameters.getTimeout_ms(), ACTION_IMG_UPLOAD);
    smp_groups->img_mgmt->start_firmware_update(image, fileName, upgrade, &imageHash);
}

void Connection::getImages(CommonParameters &parameters) {
    smp_groups->img_mgmt->set_parameters(parameters.getProtocolVersion(), parameters.getMtu(), parameters.getRetries(), parameters.getTimeout_ms(), ACTION_IMG_IMAGE_LIST);
    smp_groups->img_mgmt->start_image_get(&images_list);
}

void Connection::setImage(QByteArray *imageHash, bool confirm, CommonParameters &parameters) {
    smp_groups->img_mgmt->set_parameters(parameters.getProtocolVersion(), parameters.getMtu(), parameters.getRetries(), parameters.getTimeout_ms(), ACTION_IMG_IMAGE_SET);
    smp_groups->img_mgmt->start_image_set(imageHash, confirm, &images_list);
}

void Connection::bootLoaderInfo(QString &query) {
    smp_groups->os_mgmt->start_bootloader_info(query, &bootloader_info_response);
}

void Connection::status(uint8_t user_data, group_status status, QString error_string)
{
       /*
     *     STATUS_COMPLETE = 0,
    STATUS_ERROR,
    STATUS_TIMEOUT,
    STATUS_CANCELLED
*/

    // QLabel *label_status = nullptr;
    // bool finished = true;
    //
    // log_debug() << "Status: " << status;

    if (status == STATUS_ERROR) {
        API::sendEvent(R"({ "eventType": "error" })");
    }

    if (sender() == smp_groups->img_mgmt)
    {
        // log_debug() << "img sender";
        // label_status = lbl_IMG_Status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            //Advance to next stage of image upload
            if (user_data == ACTION_IMG_UPLOAD)
            {
//                 log_debug() << "is upload";
//
//                 if (radio_IMG_Test->isChecked() || radio_IMG_Confirm->isChecked())
//                 {
//                     //Mark image for test or confirmation
//                     finished = false;
//
//                     mode = ACTION_IMG_UPLOAD_SET;
//                     processor->set_transport(active_transport());
//                     smp_groups->img_mgmt->set_parameters((check_V2_Protocol->isChecked() ? 1 : 0), edit_MTU->value(), retries, timeout_ms, mode);
//                     bool started = smp_groups->img_mgmt->start_image_set(&upload_hash, (radio_IMG_Confirm->isChecked() ? true : false), nullptr);
// //todo: check status
//
//                     log_debug() << "do upload of " << upload_hash;
//                 }
            }
            else if (user_data == ACTION_IMG_UPLOAD_SET)
            {
//                 if (check_IMG_Reset->isChecked())
//                 {
//                     //Reboot device
//                     finished = false;
//
//                     mode = ACTION_OS_UPLOAD_RESET;
//                     processor->set_transport(active_transport());
//                     smp_groups->os_mgmt->set_parameters((check_V2_Protocol->isChecked() ? 1 : 0), edit_MTU->value(), retries, timeout_ms, mode);
//                     bool started = smp_groups->os_mgmt->start_reset(false);
// //todo: check status
//
//                     log_debug() << "do reset";
//                 }
            }
            else if (user_data == ACTION_IMG_IMAGE_LIST)
            {
                QJsonObject rootObject;
                QJsonArray imagesArray;

                uint8_t i = 0;
                while (i < images_list.length())
                {
                    auto image = images_list[i];

                    QJsonObject imageObject;
                    imageObject.insert("image", (int)image.image); // Example integer value
                    imageObject.insert("set", image.image_set); // Example boolean value
                    QJsonArray slotStatesArray;

                    for(auto j = 0; j < image.slot_list.count(); j++) {
                        auto slot = image.slot_list[j];

                        QJsonObject slotStateObject;
                        slotStateObject.insert("slot", (int)slot.slot); // Example uint32_t value
                        slotStateObject.insert("version", (QString)slot.version); // Example QByteArray value
                        slotStateObject.insert("hash", (QString)slot.hash.toHex()); // Example QByteArray value
                        slotStateObject.insert("bootable", slot.bootable); // Example boolean value
                        slotStateObject.insert("pending", slot.pending); // Example boolean value
                        slotStateObject.insert("confirmed", slot.confirmed); // Example boolean value
                        slotStateObject.insert("active", slot.active); // Example boolean value
                        slotStateObject.insert("permanent", slot.permanent); // Example boolean value
                        slotStateObject.insert("splitstatus", slot.splitstatus); // Example boolean value

                        slotStatesArray.append(slotStateObject);
                    }

                    imageObject.insert("slotStates", slotStatesArray);
                    imagesArray.append(imageObject);

                    // model_image_state.appendRow(images_list[i].item);
                    ++i;
                }

                // Convert the QJsonObject to a QByteArray
                rootObject.insert("images", imagesArray);
                QJsonDocument doc(rootObject);
                QString jsonData = doc.toJson(QJsonDocument::Compact);

                API::sendEvent(std::format("{0}\n", jsonData.toStdString()));
            }
            else if (user_data == ACTION_IMG_IMAGE_SET)
            {
                // if (parent_row != -1 && parent_column != -1 && child_row != -1 && child_column != -1)
                // {
                //     uint8_t i = 0;
                //
                //     model_image_state.clear();
                //
                //     while (i < images_list.length())
                //     {
                //         model_image_state.appendRow(images_list[i].item);
                //         ++i;
                //     }
                //
                //     if (model_image_state.hasIndex(parent_row, parent_column) == true && model_image_state.index(child_row, child_column, model_image_state.index(parent_row, parent_column)).isValid() == true)
                //     {
                //         colview_IMG_Images->setCurrentIndex(model_image_state.index(child_row, child_column, model_image_state.index(parent_row, parent_column)));
                //     }
                //     else
                //     {
                //         colview_IMG_Images->previewWidget()->hide();
                //     }
                //
                //     parent_row = -1;
                //     parent_column = -1;
                //     child_row = -1;
                //     child_column = -1;
                // }
                // else
                // {
                //     colview_IMG_Images->previewWidget()->hide();
                // }
            }
        }
        else if (status == STATUS_UNSUPPORTED)
        {
            // log_debug() << "unsupported";

            //Advance to next stage of image upload, this is likely to occur in MCUboot serial recovery whereby the image state functionality is not included
            if (user_data == ACTION_IMG_UPLOAD_SET)
            {
                // if (check_IMG_Reset->isChecked())
                // {
                //     //Reboot device
                //     finished = false;
                //
                //     mode = ACTION_OS_UPLOAD_RESET;
                //     processor->set_transport(active_transport());
                //     smp_groups->os_mgmt->set_parameters((check_V2_Protocol->isChecked() ? 1 : 0), edit_MTU->value(), retries, timeout_ms, mode);
                //     bool started = smp_groups->os_mgmt->start_reset(false);
                //     //todo: check status
                //
                //     log_debug() << "do reset";
                // }
            }
        }
    }
    else if (sender() == smp_groups->os_mgmt)
    {
        // log_debug() << "os sender";
        // label_status = lbl_OS_Status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            if (user_data == ACTION_OS_ECHO)
            {
                // edit_OS_Echo_Output->appendPlainText(error_string);
                error_string = nullptr;
            }
            else if (user_data == ACTION_OS_UPLOAD_RESET)
            {
            }
            else if (user_data == ACTION_OS_RESET)
            {
            }
            else if (user_data == ACTION_OS_MEMORY_POOL)
            {
                // uint16_t i = 0;
                // uint16_t l = table_OS_Memory->rowCount();
                //
                // table_OS_Memory->setSortingEnabled(false);
                //
                // while (i < memory_list.length())
                // {
                //     if (i >= l)
                //     {
                //         table_OS_Memory->insertRow(i);
                //
                //         QTableWidgetItem *row_name = new QTableWidgetItem(memory_list[i].name);
                //         QTableWidgetItem *row_size = new QTableWidgetItem(QString::number(memory_list[i].blocks * memory_list[i].size));
                //         QTableWidgetItem *row_free = new QTableWidgetItem(QString::number(memory_list[i].free * memory_list[i].size));
                //         QTableWidgetItem *row_minimum = new QTableWidgetItem(QString::number(memory_list[i].minimum * memory_list[i].size));
                //
                //         table_OS_Memory->setItem(i, 0, row_name);
                //         table_OS_Memory->setItem(i, 1, row_size);
                //         table_OS_Memory->setItem(i, 2, row_free);
                //         table_OS_Memory->setItem(i, 3, row_minimum);
                //     }
                //     else
                //     {
                //         table_OS_Memory->item(i, 0)->setText(memory_list[i].name);
                //         table_OS_Memory->item(i, 1)->setText(QString::number(memory_list[i].blocks * memory_list[i].size));
                //         table_OS_Memory->item(i, 2)->setText(QString::number(memory_list[i].free * memory_list[i].size));
                //         table_OS_Memory->item(i, 3)->setText(QString::number(memory_list[i].minimum * memory_list[i].size));
                //     }
                //
                //     ++i;
                // }
                //
                // while (i < l)
                // {
                //     table_OS_Memory->removeRow((table_OS_Memory->rowCount() - 1));
                //     ++i;
                // }
                //
                // table_OS_Memory->setSortingEnabled(true);
            }
            else if (user_data == ACTION_OS_TASK_STATS)
            {
                // uint16_t i = 0;
                // uint16_t l = table_OS_Tasks->rowCount();
                //
                // table_OS_Tasks->setSortingEnabled(false);
                //
                // while (i < task_list.length())
                // {
                //     if (i >= l)
                //     {
                //         table_OS_Tasks->insertRow(i);
                //
                //         QTableWidgetItem *row_name = new QTableWidgetItem(task_list[i].name);
                //         QTableWidgetItem *row_id = new QTableWidgetItem(QString::number(task_list[i].id));
                //         QTableWidgetItem *row_priority = new QTableWidgetItem(QString::number(task_list[i].priority));
                //         QTableWidgetItem *row_state = new QTableWidgetItem(QString::number(task_list[i].state));
                //         QTableWidgetItem *row_context_switches = new QTableWidgetItem(QString::number(task_list[i].context_switches));
                //         QTableWidgetItem *row_runtime = new QTableWidgetItem(QString::number(task_list[i].runtime));
                //         QTableWidgetItem *row_stack_size = new QTableWidgetItem(QString::number(task_list[i].stack_size * 4));
                //         QTableWidgetItem *row_stack_usage = new QTableWidgetItem(QString::number(task_list[i].stack_usage * 4));
                //
                //         table_OS_Tasks->setItem(i, 0, row_name);
                //         table_OS_Tasks->setItem(i, 1, row_id);
                //         table_OS_Tasks->setItem(i, 2, row_priority);
                //         table_OS_Tasks->setItem(i, 3, row_state);
                //         table_OS_Tasks->setItem(i, 4, row_context_switches);
                //         table_OS_Tasks->setItem(i, 5, row_runtime);
                //         table_OS_Tasks->setItem(i, 6, row_stack_size);
                //         table_OS_Tasks->setItem(i, 7, row_stack_usage);
                //     }
                //     else
                //     {
                //         table_OS_Tasks->item(i, 0)->setText(task_list[i].name);
                //         table_OS_Tasks->item(i, 1)->setText(QString::number(task_list[i].id));
                //         table_OS_Tasks->item(i, 2)->setText(QString::number(task_list[i].priority));
                //         table_OS_Tasks->item(i, 3)->setText(QString::number(task_list[i].state));
                //         table_OS_Tasks->item(i, 4)->setText(QString::number(task_list[i].context_switches));
                //         table_OS_Tasks->item(i, 5)->setText(QString::number(task_list[i].runtime));
                //         table_OS_Tasks->item(i, 6)->setText(QString::number(task_list[i].stack_size * sizeof(uint32_t)));
                //         table_OS_Tasks->item(i, 7)->setText(QString::number(task_list[i].stack_usage * sizeof(uint32_t)));
                //     }
                //
                //     ++i;
                // }
                //
                // while (i < l)
                // {
                //     table_OS_Tasks->removeRow((table_OS_Tasks->rowCount() - 1));
                //     ++i;
                // }
                //
                // table_OS_Tasks->setSortingEnabled(true);
            }
            else if (user_data == ACTION_OS_MCUMGR_BUFFER)
            {
                // edit_OS_Info_Output->clear();
                // edit_OS_Info_Output->appendPlainText(error_string);
                error_string = nullptr;
            }
            else if (user_data == ACTION_OS_OS_APPLICATION_INFO)
            {
                // edit_OS_Info_Output->clear();
                // edit_OS_Info_Output->appendPlainText(error_string);
                error_string = nullptr;
            }
            else if (user_data == ACTION_OS_BOOTLOADER_INFO)
            {
                switch (bootloader_info_response.type())
                {
                    case QVariant::Bool:
                    {
                        // edit_os_bootloader_response->setText(bootloader_info_response.toBool() == true ? "True" : "False");
                        break;
                    }

                    case QVariant::Int:
                    {
                        // edit_os_bootloader_response->setText(QString::number(bootloader_info_response.toInt()));
                        break;
                    }

                    case QVariant::LongLong:
                    {
                        // edit_os_bootloader_response->setText(QString::number(bootloader_info_response.toLongLong()));
                        break;
                    }

                    case QVariant::UInt:
                    {
                        // edit_os_bootloader_response->setText(QString::number(bootloader_info_response.toUInt()));
                        break;
                    }

                    case QVariant::ULongLong:
                    {
                        // edit_os_bootloader_response->setText(QString::number(bootloader_info_response.toULongLong()));
                        break;
                    }

                    case QVariant::Double:
                    {
                        // edit_os_bootloader_response->setText(QString::number(bootloader_info_response.toDouble()));
                        break;
                    }

                    case QVariant::String:
                    {
                        // edit_os_bootloader_response->setText(bootloader_info_response.toString());
                        break;
                    }

                    default:
                    {
                        error_string = "Invalid";
                    }
                }
            }
            else if (user_data == ACTION_OS_DATETIME_GET)
            {
                // int index;
                // log_debug() << "RTC response: " << rtc_time_date_response;
                //
                // rtc_time_date_response.setTimeZone(rtc_time_date_response.timeZone());
                // index = combo_os_datetime_timezone->findText(rtc_time_date_response.timeZone().displayName(rtc_time_date_response, QTimeZone::OffsetName));
                //
                // if (index >= 0)
                // {
                //     combo_os_datetime_timezone->setCurrentIndex(index);
                // }
                //
                // edit_os_datetime_date_time->setDateTime(rtc_time_date_response);
            }
            else if (user_data == ACTION_OS_DATETIME_SET)
            {
            }
        }
    }
    else if (sender() == smp_groups->shell_mgmt)
    {
        // log_debug() << "shell sender";
        // label_status = lbl_SHELL_Status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            if (user_data == ACTION_SHELL_EXECUTE)
            {
                // edit_SHELL_Output->add_dat_in_text(error_string.toUtf8());
                //
                // if (shell_rc == 0)
                // {
                //     error_string = nullptr;
                // }
                // else
                // {
                //     error_string = QString("Finished, error (ret): ").append(QString::number(shell_rc));
                // }
            }
        }
    }
    else if (sender() == smp_groups->stat_mgmt)
    {
        // log_debug() << "stat sender";
        // label_status = lbl_STAT_Status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            if (user_data == ACTION_STAT_GROUP_DATA)
            {
                // uint16_t i = 0;
                // uint16_t l = table_STAT_Values->rowCount();
                //
                // table_STAT_Values->setSortingEnabled(false);
                //
                // while (i < stat_list.length())
                // {
                //     if (i >= l)
                //     {
                //         // table_STAT_Values->insertRow(i);
                //         //
                //         // QTableWidgetItem *row_name = new QTableWidgetItem(stat_list[i].name);
                //         // QTableWidgetItem *row_value = new QTableWidgetItem(QString::number(stat_list[i].value));
                //         //
                //         //
                //         // table_STAT_Values->setItem(i, 0, row_name);
                //         // table_STAT_Values->setItem(i, 1, row_value);
                //     }
                //     else
                //     {
                //         // table_STAT_Values->item(i, 0)->setText(stat_list[i].name);
                //         // table_STAT_Values->item(i, 1)->setText(QString::number(stat_list[i].value));
                //     }
                //
                //     ++i;
                // }

                // while (i < l)
                // {
                //     // table_STAT_Values->removeRow((table_STAT_Values->rowCount() - 1));
                //     ++i;
                // }

                // table_STAT_Values->setSortingEnabled(true);
            }
            else if (user_data == ACTION_STAT_LIST_GROUPS)
            {
                // combo_STAT_Group->clear();
                // combo_STAT_Group->addItems(group_list);
            }
        }
    }
    else if (sender() == smp_groups->fs_mgmt)
    {
        // log_debug() << "fs sender";
        // label_status = lbl_FS_Status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            if (user_data == ACTION_FS_UPLOAD)
            {
                //edit_FS_Log->appendPlainText("todo");
            }
            else if (user_data == ACTION_FS_DOWNLOAD)
            {
                //edit_FS_Log->appendPlainText("todo2");
            }
            else if (user_data == ACTION_FS_HASH_CHECKSUM)
            {
                error_string.prepend("Finished hash/checksum using ");
                // edit_FS_Result->setText(fs_hash_checksum_response.toHex());
                // edit_FS_Size->setText(QString::number(fs_size_response));
            }
            else if (user_data == ACTION_FS_SUPPORTED_HASHES_CHECKSUMS)
            {
                uint8_t i = 0;

                // combo_FS_type->clear();

                while (i < supported_hash_checksum_list.length())
                {
                    // combo_FS_type->addItem(supported_hash_checksum_list.at(i).name);
                    // log_debug() << supported_hash_checksum_list.at(i).format << ", " << supported_hash_checksum_list.at(i).size;
                    ++i;
                }
            }
            else if (user_data == ACTION_FS_STATUS)
            {
                // edit_FS_Size->setText(QString::number(fs_size_response));
            }
        }
    }
    else if (sender() == smp_groups->settings_mgmt)
    {
        // log_debug() << "settings sender";
        // label_status = lbl_settings_status;

        if (status == STATUS_COMPLETE)
        {
            // log_debug() << "complete";

            if (user_data == ACTION_SETTINGS_READ)
            {
                // edit_settings_value->setText(settings_read_response.toHex());
                //
                // if (update_settings_display() == false)
                // {
                //     error_string = QString("Error: data is %1 bytes, cannot convert to decimal number").arg(QString::number(settings_read_response.length()));
                // }
            }
            else if (user_data == ACTION_SETTINGS_WRITE || user_data == ACTION_SETTINGS_DELETE || user_data == ACTION_SETTINGS_COMMIT || user_data == ACTION_SETTINGS_LOAD || user_data == ACTION_SETTINGS_SAVE)
            {
            }
        }
    }
    else if (sender() == smp_groups->zephyr_mgmt)
    {
        // log_debug() << "zephyr sender";
        // label_status = lbl_zephyr_status;

        if (user_data == ACTION_ZEPHYR_STORAGE_ERASE)
        {
        }
    }

    // if (finished == true)
    // {
    //     // mode = ACTION_IDLE;
    //     // relase_transport();
    //
    //     if (error_string == nullptr)
    //     {
    //         if (status == STATUS_COMPLETE)
    //         {
    //             error_string = QString("Finished");
    //         }
    //         else if (status == STATUS_ERROR)
    //         {
    //             error_string = QString("Error");
    //         }
    //         else if (status == STATUS_TIMEOUT)
    //         {
    //             error_string = QString("Command timed out");
    //         }
    //         else if (status == STATUS_CANCELLED)
    //         {
    //             error_string = QString("Cancelled");
    //         }
    //     }
    // }
    //
    // if (error_string != nullptr)
    // {
    //     if (label_status != nullptr)
    //     {
    //         label_status->setText(error_string);
    //     }
    //     else
    //     {
    //         //log_error() << "Status message (no receiver): " << error_string;
    //     }
    // }
}

void Connection::progress(uint8_t user_data, uint8_t percent)
{
    Q_UNUSED(user_data);

    // log_debug() << "Progress " << percent << " from " << this->sender();
    //
    // if (this->sender() == smp_groups->img_mgmt)
    // {
    //     log_debug() << "img sender";
    //     progress_IMG_Complete->setValue(percent);
    // }
    // else if (this->sender() == smp_groups->fs_mgmt)
    // {
    //     log_debug() << "fs sender";
    //     progress_FS_Complete->setValue(percent);
    // }
}
