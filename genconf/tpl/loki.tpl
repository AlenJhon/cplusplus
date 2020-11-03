auth_enabled: false

#配置启动的模块的服务器
server:
  http_listen_port: {{http_listen_port}}


ingester:
  lifecycler:
    address: {{address}} #127.0.0.1
    ring:
      kvstore:
        store: inmemory
      replication_factor: 1
    final_sleep: 0s
  chunk_idle_period: 30m     
  chunk_retain_period: 15m    

#该schema_config块从给定日期配置模式。
schema_config:
  configs:
    - from: {{index_from}}#2020-10-24
      store: boltdb
      object_store: filesystem
      schema: v11
      index:
        prefix: index_
        period: {{index_period}}#48h


#配置Loki将存储数据的位置。
storage_config:
  boltdb:
    directory: {{boltdb_dir}} #/data/loki/index
#配置将块存储在本地文件系统上。所需
  filesystem:
    directory: {{chunks_dir}} #/data/loki/chunks

limits_config:
  reject_old_samples: true
  enforce_metric_name: false
  reject_old_samples_max_age: 168h
  ingestion_rate_mb: {{ingestion_rate_mb}} #150

chunk_store_config:
  # 最大可查询历史日期 90天
  max_look_back_period: {{max_look_back_period}} #2160h