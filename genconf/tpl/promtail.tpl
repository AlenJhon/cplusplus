server:
  http_listen_port: {{http_listen_port}}

positions:
  filename: {{positions_filename}} #记录当前日志采集状态的文件地址(promtail自动生产)

clients:
  - url: {{loki_url}} #采集的日志投递loki的地址

scrape_configs:
{%- for jobx in job_lists %}
- job_name: {{jobx.job_name}}
  static_configs:
  - targets:
      - localhost
    labels:
      job: {{jobx.job}}
      hosts: {{jobx.hosts}}
      __path__: {{jobx.path}} # log path
{%- endfor %}